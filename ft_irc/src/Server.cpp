
#include "Server.hpp"

#include <algorithm>
#include <cerrno>
#include <cctype>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <poll.h>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>

namespace
{
	const char *SERVER_NAME = "ircserv.local";
	const std::size_t MAX_LINE_LENGTH = 510;
	const std::size_t MAX_INPUT_LENGTH = 8192;
	const std::size_t MAX_OUTPUT_LENGTH = 1048576;
	const std::size_t MAX_USERNAME_LENGTH = 32;
	const std::time_t CLOSE_TIMEOUT_SECONDS = 5;
	volatile sig_atomic_t g_running = 1;

	void stopServer(int)
	{
		g_running = 0;
	}

	std::string numberString(int value)
	{
		std::ostringstream stream;
		stream << value;
		return stream.str();
	}

	std::string numberString(unsigned long value)
	{
		std::ostringstream stream;
		stream << value;
		return stream.str();
	}

	std::vector<std::string> splitPreservingEmpty(const std::string &text,
		char delimiter)
	{
		std::vector<std::string> result;
		std::string::size_type start = 0;
		while (true)
		{
			std::string::size_type end = text.find(delimiter, start);
			result.push_back(text.substr(start,
				end == std::string::npos ? std::string::npos : end - start));
			if (end == std::string::npos)
				break;
			start = end + 1;
		}
		return result;
	}
}

Client::Client()
	: fd(-1), passwordAccepted(false), hasNickname(false), hasUser(false),
	  capNegotiating(false), registered(false), closing(false), forceClose(false),
	  closeDeadline(0)
{
}

Channel::Channel()
	: inviteOnly(false), topicRestricted(false), userLimit(0)
{
}

bool Channel::hasMember(int fd) const
{
	return members.find(fd) != members.end();
}

bool Channel::isOperator(int fd) const
{
	std::map<int, bool>::const_iterator member = members.find(fd);
	return member != members.end() && member->second;
}

Server::Server(const std::string &port, const std::string &password)
	: listener_(-1), port_(port), password_(password)
{
	createListener(port);
	std::signal(SIGINT, stopServer);
	std::signal(SIGTERM, stopServer);
	std::signal(SIGPIPE, SIG_IGN);
}

Server::~Server()
{
	if (listener_ >= 0)
		close(listener_);
	for (std::map<int, Client>::iterator it = clients_.begin();
		 it != clients_.end(); ++it)
		close(it->first);
}

void Server::createListener(const std::string &port)
{
	struct addrinfo hints;
	std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	struct addrinfo *addresses = NULL;
	int result = getaddrinfo(NULL, port.c_str(), &hints, &addresses);
	if (result != 0)
		throw std::runtime_error(std::string("getaddrinfo: ") + gai_strerror(result));

	int reuseAddress = 1;
	for (struct addrinfo *address = addresses; address != NULL;
		 address = address->ai_next)
	{
		int fd = socket(address->ai_family, address->ai_socktype,
			address->ai_protocol);
		if (fd < 0)
			continue;
		if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuseAddress,
			sizeof(reuseAddress)) < 0
			|| fcntl(fd, F_SETFL, O_NONBLOCK) < 0
			|| bind(fd, address->ai_addr, address->ai_addrlen) < 0
			|| listen(fd, 128) < 0)
		{
			close(fd);
			continue;
		}
		listener_ = fd;
		break;
	}
	freeaddrinfo(addresses);
	if (listener_ < 0)
		throw std::runtime_error("could not create listening socket");
}

void Server::run()
{
	std::cout << "Listening on port " << port_ << " (password-protected)"
		<< std::endl;
	while (g_running)
	{
		closeReadyClients();
		int pollTimeout = -1;
		std::time_t nextCloseDeadline = 0;
		for (std::map<int, Client>::const_iterator it = clients_.begin();
			 it != clients_.end(); ++it)
		{
			if (it->second.closing && !it->second.forceClose
				&& !it->second.output.empty()
				&& (nextCloseDeadline == 0
					|| it->second.closeDeadline < nextCloseDeadline))
				nextCloseDeadline = it->second.closeDeadline;
		}
		if (nextCloseDeadline != 0)
		{
			std::time_t now = std::time(NULL);
			if (now == static_cast<std::time_t>(-1)
				|| nextCloseDeadline <= now)
				pollTimeout = 0;
			else
				pollTimeout = static_cast<int>((nextCloseDeadline - now) * 1000);
		}
		std::vector<struct pollfd> descriptors;
		struct pollfd listening;
		listening.fd = listener_;
		listening.events = POLLIN;
		listening.revents = 0;
		descriptors.push_back(listening);

		for (std::map<int, Client>::const_iterator it = clients_.begin();
			 it != clients_.end(); ++it)
		{
			struct pollfd descriptor;
			descriptor.fd = it->first;
			descriptor.events = it->second.closing ? 0 : POLLIN;
			if (!it->second.output.empty())
				descriptor.events |= POLLOUT;
			descriptor.revents = 0;
			descriptors.push_back(descriptor);
		}

		int ready = poll(&descriptors[0], descriptors.size(), pollTimeout);
		if (ready < 0)
		{
			if (errno == EINTR)
				continue;
			throw std::runtime_error("poll failed");
		}
		if (ready == 0)
		{
			closeReadyClients();
			continue;
		}
		if (descriptors[0].revents & (POLLERR | POLLHUP | POLLNVAL))
			throw std::runtime_error("listening socket poll error");
		if (descriptors[0].revents & POLLIN)
			acceptClient();

		for (std::size_t i = 1; i < descriptors.size(); ++i)
		{
			const int fd = descriptors[i].fd;
			std::map<int, Client>::iterator client = clients_.find(fd);
			if (client == clients_.end())
				continue;
			short events = descriptors[i].revents;
			if (events & (POLLERR | POLLNVAL))
			{
				closeClient(fd, "Connection error");
				continue;
			}
			if ((events & POLLIN) && !client->second.closing)
			{
				IoResult result = readClient(fd);
				if (result == IO_DISCONNECTED)
				{
					closeClient(fd, "Connection closed");
					continue;
				}
			}
			client = clients_.find(fd);
			if (client == clients_.end())
				continue;
			if ((events & POLLOUT) && !client->second.output.empty())
			{
				IoResult result = writeClient(fd);
				if (result == IO_DISCONNECTED)
				{
					closeClient(fd, "Send returned zero");
					continue;
				}
			}
			client = clients_.find(fd);
			if (client == clients_.end())
				continue;
			if (events & POLLHUP)
			{
				closeClient(fd, "Connection closed");
				continue;
			}
			if (client->second.forceClose
				|| (client->second.closing && client->second.output.empty()))
				closeClient(fd, client->second.closeReason);
		}
	}
}

void Server::acceptClient()
{
	struct sockaddr_in address;
	socklen_t addressLength = sizeof(address);
	int fd = accept(listener_, reinterpret_cast<struct sockaddr *>(&address),
		&addressLength);
	if (fd < 0)
		return;
	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
	{
		close(fd);
		return;
	}
	Client client;
	client.fd = fd;
	clients_.insert(std::make_pair(fd, client));
}

Server::IoResult Server::readClient(int fd)
{
	char buffer[4096];
	ssize_t received = recv(fd, buffer, sizeof(buffer), 0);
	std::map<int, Client>::iterator it = clients_.find(fd);
	if (it == clients_.end())
		return IO_DISCONNECTED;
	if (received == 0)
		return IO_DISCONNECTED;
	if (received < 0)
		return IO_DEFERRED;
	it->second.input.append(buffer, static_cast<std::size_t>(received));
	processInput(it->second);
	if (!it->second.closing && it->second.input.size() > MAX_INPUT_LENGTH)
	{
		numeric(it->second, 417, ":Input buffer too large");
		beginGracefulClose(it->second, "Input buffer too large");
		it->second.input.clear();
	}
	return IO_PROGRESS;
}

Server::IoResult Server::writeClient(int fd)
{
	std::map<int, Client>::iterator it = clients_.find(fd);
	if (it == clients_.end() || it->second.output.empty())
		return IO_PROGRESS;
	ssize_t sent = send(fd, it->second.output.data(), it->second.output.size(), 0);
	if (sent > 0)
	{
		it->second.output.erase(0, static_cast<std::size_t>(sent));
		return IO_PROGRESS;
	}
	if (sent == 0)
		return IO_DISCONNECTED;
	return IO_DEFERRED;
}

void Server::closeReadyClients()
{
	std::time_t now = std::time(NULL);
	for (;;)
	{
		std::map<int, Client>::iterator client = clients_.begin();
		while (client != clients_.end())
		{
			if (client->second.forceClose)
				break;
			if (client->second.closing)
			{
				bool deadlineExpired = now == static_cast<std::time_t>(-1)
					|| client->second.closeDeadline <= now;
				if (client->second.output.empty() || deadlineExpired)
					break;
			}
			++client;
		}
		if (client == clients_.end())
			return;
		int fd = client->first;
		std::string reason = client->second.closeReason;
		closeClient(fd, reason);
	}
}

void Server::beginGracefulClose(Client &client, const std::string &reason)
{
	if (client.closing)
		return;
	std::time_t now = std::time(NULL);
	client.closing = true;
	client.closeReason = reason;
	if (now == static_cast<std::time_t>(-1))
	{
		client.forceClose = true;
		client.output.clear();
		return;
	}
	client.closeDeadline = now + CLOSE_TIMEOUT_SECONDS;
}

void Server::processInput(Client &client)
{
	while (!client.closing)
	{
		std::string::size_type newline = client.input.find('\n');

		if (newline == std::string::npos)
		{
			std::size_t incompleteLength = client.input.size();
			if (!client.input.empty()
				&& client.input[client.input.size() - 1] == '\r')
				--incompleteLength;
			if (incompleteLength > MAX_LINE_LENGTH)
			{
				numeric(client, 417, ":Input line too long");
				client.input.clear();
				beginGracefulClose(client, "Input line too long");
			}
			return;
		}
		std::string line = client.input.substr(0, newline);
		client.input.erase(0, newline + 1);
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);
		if (line.size() > MAX_LINE_LENGTH)
		{
			numeric(client, 417, ":Input line too long");
			continue;
		}
		if (line.find('\r') != std::string::npos
			|| line.find('\0') != std::string::npos)
		{
			numeric(client, 417, ":Input line contains invalid control character");
			continue;
		}
		processLine(client, line);
	}
}

void Server::processLine(Client &client, const std::string &line)
{
	std::string::size_type position = 0;
	while (position < line.size() && line[position] == ' ')
		++position;
	if (position == line.size())
		return;
	if (line[position] == ':')
	{
		std::string::size_type prefixEnd = line.find(' ', position);
		if (prefixEnd == std::string::npos)
			return;
		position = prefixEnd + 1;
	}
	while (position < line.size() && line[position] == ' ')
		++position;
	std::string::size_type commandEnd = line.find(' ', position);
	std::string command = upper(line.substr(position,
		commandEnd == std::string::npos ? std::string::npos : commandEnd - position));
	if (command.empty())
		return;
	std::vector<std::string> params;
	position = commandEnd == std::string::npos ? line.size() : commandEnd + 1;
	bool trailingParameter = false;
	while (position < line.size() && params.size() < 15)
	{
		while (position < line.size() && line[position] == ' ')
			++position;
		if (position == line.size())
			break;
		if (line[position] == ':')
		{
			params.push_back(line.substr(position + 1));
			trailingParameter = true;
			break;
		}
		std::string::size_type end = line.find(' ', position);
		params.push_back(line.substr(position,
			end == std::string::npos ? std::string::npos : end - position));
		position = end == std::string::npos ? line.size() : end + 1;
	}
	if (!trailingParameter && params.size() == 15)
	{
		while (position < line.size() && line[position] == ' ')
			++position;
		if (position < line.size())
		{
			numeric(client, 461, command + " :Too many parameters");
			return;
		}
	}
	processCommand(client, command, params);
}

void Server::processCommand(Client &client, const std::string &command,
	const std::vector<std::string> &params)
{
	if (command == "PASS")
	{
		if (client.registered)
			numeric(client, 462, ":You may not reregister");
		else if (params.empty())
			numeric(client, 461, "PASS :Not enough parameters");
		else if (params[0] != password_)
		{
			numeric(client, 464, ":Password incorrect");
			beginGracefulClose(client, "Password incorrect");
		}
		else
		{
			client.passwordAccepted = true;
			tryRegister(client);
		}
		return;
	}
	if (command == "NICK")
	{
		if (params.empty())
		{
			numeric(client, 431, ":No nickname given");
			return;
		}
		if (!validNickname(params[0]))
		{
			numeric(client, 432, params[0] + " :Erroneous nickname");
			return;
		}
		Client *existing = findNickname(params[0]);
		if (existing != NULL && existing->fd != client.fd)
		{
			numeric(client, 433, params[0] + " :Nickname is already in use");
			return;
		}
		std::string oldPrefix;
		if (client.registered)
			oldPrefix = clientPrefix(client);
		client.nickname = params[0];
		client.hasNickname = true;
		if (!oldPrefix.empty())
		{
			std::string message = makeTrailingLine(oldPrefix + " NICK :",
				client.nickname);
			std::set<int> recipients;
			for (std::map<std::string, Channel>::const_iterator channel =
				 channels_.begin(); channel != channels_.end(); ++channel)
			{
				if (channel->second.hasMember(client.fd))
				{
					for (std::map<int, bool>::const_iterator member =
						 channel->second.members.begin();
						 member != channel->second.members.end(); ++member)
						recipients.insert(member->first);
				}
			}
			for (std::set<int>::const_iterator recipient = recipients.begin();
				 recipient != recipients.end(); ++recipient)
			{
				std::map<int, Client>::iterator target = clients_.find(*recipient);
				if (target != clients_.end())
					queue(target->second, message);
			}
		}
		tryRegister(client);
		return;
	}
	if (command == "USER")
	{
		if (client.registered || client.hasUser)
		{
			numeric(client, 462, ":You may not reregister");
			return;
		}
		if (params.size() < 4)
		{
			numeric(client, 461, "USER :Not enough parameters");
			return;
		}
		bool validUsername = !params[0].empty()
			&& params[0].size() <= MAX_USERNAME_LENGTH;
		for (std::string::size_type i = 0;
			 validUsername && i < params[0].size(); ++i)
		{
			unsigned char character =
				static_cast<unsigned char>(params[0][i]);
			if (character <= 32 || character == 127
				|| params[0][i] == '@' || params[0][i] == '!')
				validUsername = false;
		}
		if (!validUsername)
		{
			numeric(client, 461, "USER :Invalid username");
			return;
		}
		client.username = params[0];
		client.realname = params[3];
		client.hasUser = true;
		tryRegister(client);
		return;
	}
	if (command == "CAP")
	{
		std::string target = nicknameOrStar(client);
		if (params.empty())
			return;
		std::string subcommand = upper(params[0]);
		if (subcommand == "LS")
		{
			if (!client.registered)
				client.capNegotiating = true;
			queue(client, ":" + std::string(SERVER_NAME) + " CAP " + target
				+ " LS :\r\n");
		}
		else if (subcommand == "LIST")
			queue(client, ":" + std::string(SERVER_NAME) + " CAP " + target
				+ " LIST :\r\n");
		else if (subcommand == "REQ")
			queue(client, makeTrailingLine(":" + std::string(SERVER_NAME)
				+ " CAP " + target + " NAK :",
				params.size() > 1 ? params[1] : ""));
		else if (subcommand == "END")
		{
			client.capNegotiating = false;
			tryRegister(client);
		}
		return;
	}
	if (command == "PING")
	{
		if (params.empty())
			numeric(client, 409, ":No origin specified");
		else
			queue(client, makeTrailingLine(":" + std::string(SERVER_NAME)
				+ " PONG " + SERVER_NAME + " :", params[0]));
		return;
	}
	if (command == "QUIT")
	{
		beginGracefulClose(client,
			params.empty() ? "Client Quit" : params[0]);
		return;
	}
	if (!client.registered)
	{
		numeric(client, 451, ":You have not registered");
		return;
	}
	if (command == "JOIN")
	{
		handleJoin(client, params);
		return;
	}
	if (command == "PRIVMSG" || command == "NOTICE")
	{
		handlePrivmsg(client, command, params);
		return;
	}
	if (command == "PART")
	{
		if (params.empty())
		{
			numeric(client, 461, "PART :Not enough parameters");
			return;
		}
		std::vector<std::string> names = split(params[0], ',');
		for (std::size_t i = 0; i < names.size(); ++i)
		{
			Channel *channel = findChannel(names[i]);
			if (channel == NULL)
			{
				numeric(client, 403, names[i] + " :No such channel");
				continue;
			}
			if (!channel->hasMember(client.fd))
			{
				numeric(client, 442, names[i] + " :You are not on that channel");
				continue;
			}
			std::string reason = params.size() > 1 ? params[1] : client.nickname;
			removeFromChannel(client.fd, names[i], makeTrailingLine(
				clientPrefix(client) + " PART " + names[i] + " :", reason));
		}
		return;
	}

	if (command == "NAMES")
	{
		if (params.empty())
		{
			bool foundChannel = false;
			std::set<int> channelMembers;

			for (std::map<std::string, Channel>::const_iterator channel =
				 channels_.begin(); channel != channels_.end(); ++channel)
			{
				foundChannel = true;

				for (std::map<int, bool>::const_iterator member =
					 channel->second.members.begin();
					 member != channel->second.members.end(); ++member)
				{
					channelMembers.insert(member->first);
				}

				sendNames(client, channel->second);
			}

			std::string names;
			std::string namesPrefix = ":" + std::string(SERVER_NAME) + " 353 "
				+ nicknameOrStar(client) + " * * :";
			std::size_t available = MAX_LINE_LENGTH - namesPrefix.size();
			bool foundUnchanneledUser = false;

			for (std::map<int, Client>::const_iterator user = clients_.begin();
				 user != clients_.end(); ++user)
			{
				if (!user->second.registered
					|| channelMembers.find(user->first) != channelMembers.end())
					continue;

				std::string::size_type separator = names.empty() ? 0 : 1;

				if (!names.empty()
					&& names.size() + separator + user->second.nickname.size()
						> available)
				{
					numeric(client, 353, "* * :" + names);
					names.clear();
					separator = 0;
				}

				if (user->second.nickname.size() + separator <= available)
				{
					if (separator != 0)
						names += " ";

					names += user->second.nickname;
					foundUnchanneledUser = true;
				}
			}

			if (!names.empty())
				numeric(client, 353, "* * :" + names);

			if (foundUnchanneledUser || !foundChannel)
				numeric(client, 366, "* :End of /NAMES list");
		}
		else
		{
			std::vector<std::string> names = split(params[0], ',');

			for (std::size_t i = 0; i < names.size(); ++i)
			{
				Channel *channel = findChannel(names[i]);

				if (channel != NULL)
					sendNames(client, *channel);
				else
					numeric(client, 366,
						names[i] + " :End of /NAMES list");
			}
		}

		return;
	}

	if (command == "TOPIC")
	{
		if (params.empty())
		{
			numeric(client, 461, "TOPIC :Not enough parameters");
			return;
		}
		Channel *channel = findChannel(params[0]);
		if (channel == NULL)
		{
			numeric(client, 403, params[0] + " :No such channel");
			return;
		}
		if (params.size() == 1)
		{
			if (channel->topic.empty())
				numeric(client, 331, channel->name + " :No topic is set");
			else
				numeric(client, 332, channel->name + " :" + channel->topic);
			return;
		}
		if (!channel->hasMember(client.fd))
		{
			numeric(client, 442, channel->name + " :You are not on that channel");
			return;
		}
		if (channel->topicRestricted && !channel->isOperator(client.fd))
		{
			numeric(client, 482, channel->name + " :You are not channel operator");
			return;
		}
		std::string topicPrefix = clientPrefix(client) + " TOPIC "
			+ channel->name + " :";
		std::string topicLine = makeTrailingLine(topicPrefix, params[1]);
		if (topicLine.empty())
		{
			numeric(client, 696, channel->name
				+ " t :Topic line is too long");
			return;
		}
		channel->topic = topicLine.substr(topicPrefix.size(),
			topicLine.size() - topicPrefix.size() - 2);
		sendToChannel(*channel, topicLine, -1);
		return;
	}
	if (command == "INVITE")
	{
		if (params.size() < 2)
		{
			numeric(client, 461, "INVITE :Not enough parameters");
			return;
		}
		Client *target = findNickname(params[0]);
		if (target == NULL || !target->registered)
		{
			numeric(client, 401, params[0] + " :No such nick");
			return;
		}
		Channel *channel = findChannel(params[1]);
		if (channel == NULL)
		{
			numeric(client, 403, params[1] + " :No such channel");
			return;
		}
		if (!channel->hasMember(client.fd))
		{
			numeric(client, 442, channel->name + " :You are not on that channel");
			return;
		}
		if (channel->inviteOnly && !channel->isOperator(client.fd))
		{
			numeric(client, 482, channel->name + " :You are not channel operator");
			return;
		}
		if (channel->hasMember(target->fd))
		{
			numeric(client, 443, target->nickname + " " + channel->name
				+ " :is already on channel");
			return;
		}
		channel->invitations.insert(target->fd);
		numeric(client, 341, target->nickname + " " + channel->name);
		queue(*target, makeTrailingLine(clientPrefix(client) + " INVITE "
			+ target->nickname + " :", channel->name));
		return;
	}
	if (command == "KICK")
	{
		if (params.size() < 2)
		{
			numeric(client, 461, "KICK :Not enough parameters");
			return;
		}
		Channel *channel = findChannel(params[0]);
		if (channel == NULL)
		{
			numeric(client, 403, params[0] + " :No such channel");
			return;
		}
		if (!channel->hasMember(client.fd))
		{
			numeric(client, 442, channel->name + " :You are not on that channel");
			return;
		}
		if (!channel->isOperator(client.fd))
		{
			numeric(client, 482, channel->name + " :You are not channel operator");
			return;
		}
		Client *target = findNickname(params[1]);
		if (target == NULL || !channel->hasMember(target->fd))
		{
			numeric(client, 441, params[1] + " " + channel->name
				+ " :They aren't on that channel");
			return;
		}
		std::string reason = params.size() > 2 ? params[2] : client.nickname;
		removeFromChannel(target->fd, channel->name, makeTrailingLine(
			clientPrefix(client) + " KICK " + channel->name + " "
				+ target->nickname + " :", reason));
		return;
	}
	if (command == "MODE")
	{
		if (!params.empty() && !params[0].empty() && params[0][0] != '#'
			&& params[0][0] != '&')
		{
			Client *target = findNickname(params[0]);
			if (target == NULL)
			{
				numeric(client, 401, params[0] + " :No such nick");
				return;
			}
			if (target->fd != client.fd)
			{
				numeric(client, 502, ":Cannot change mode for other users");
				return;
			}
			if (params.size() == 1)
			{
				numeric(client, 221, "+" + client.userModes);
				return;
			}
			bool adding = true;
			for (std::string::size_type i = 0; i < params[1].size(); ++i)
			{
				char mode = params[1][i];
				if (mode == '+' || mode == '-')
				{
					adding = mode == '+';
					continue;
				}
				if (mode != 'i' && mode != 'w')
				{
					numeric(client, 501, ":Unknown MODE flag");
					continue;
				}
				std::string::size_type existing = client.userModes.find(mode);
				if (adding && existing == std::string::npos)
					client.userModes += mode;
				else if (!adding && existing != std::string::npos)
					client.userModes.erase(existing, 1);
			}
			numeric(client, 221, "+" + client.userModes);
			return;
		}
		handleMode(client, params);
		return;
	}
	if (command == "WHO")
	{
		handleWho(client, params);
		return;
	}
	if (command == "WHOIS")
	{
		handleWhois(client, params);
		return;
	}
	if (command == "LUSERS")
	{
		int registeredClients = 0;
		for (std::map<int, Client>::const_iterator it = clients_.begin();
			 it != clients_.end(); ++it)
		{
			if (it->second.registered)
				++registeredClients;
		}
		numeric(client, 251, ":There are " + numberString(
			registeredClients) + " users and 0 services on 1 server");
		numeric(client, 255, ":I have " + numberString(
			registeredClients) + " clients and 1 servers");
		return;
	}
	if (command == "MOTD")
	{
		numeric(client, 422, ":MOTD file is missing");
		return;
	}
	if (command == "AWAY")
	{
		if (params.empty() || params[0].empty())
		{
			client.awayMessage.clear();
			numeric(client, 305, ":You are no longer marked as being away");
		}
		else
		{
			client.awayMessage = params[0];
			numeric(client, 306, ":You have been marked as being away");
		}
		return;
	}
	numeric(client, 421, command + " :Unknown command");
}

void Server::tryRegister(Client &client)
{
	if (client.registered || client.capNegotiating || !client.passwordAccepted
		|| !client.hasNickname || !client.hasUser)
		return;
	client.registered = true;
	numeric(client, 1, ":Welcome to the Internet Relay Network "
		+ client.nickname + "!" + client.username + "@localhost");
	numeric(client, 2, ":Your host is ircserv.local, running version 1.0");
	numeric(client, 3, ":This server was created today");
	numeric(client, 4, "ircserv.local 1.0 itkol");
	numeric(client, 422, ":MOTD file is missing");
}

void Server::queue(Client &client, const std::string &message)
{
	if (client.closing)
		return;
	if (message.size() < 2 || message.size() > MAX_LINE_LENGTH + 2
		|| message.compare(message.size() - 2, 2, "\r\n") != 0
		|| message.find('\r') != message.size() - 2
		|| message.find('\n') != message.size() - 1)
	{
		std::cerr << "ircserv: rejected invalid outbound IRC line for client "
			<< client.fd << std::endl;
		return;
	}
	if (message.size() > MAX_OUTPUT_LENGTH
		|| client.output.size() > MAX_OUTPUT_LENGTH - message.size())
	{
		client.closing = true;
		client.forceClose = true;
		client.closeReason = "Output buffer limit exceeded";
		client.output.clear();
		return;
	}
	client.output += message;
}

std::string Server::makeTrailingLine(const std::string &prefix,
	const std::string &text) const
{
	if (prefix.size() > MAX_LINE_LENGTH)
		return "";
	std::string safeText = text;
	safeText.erase(std::remove(safeText.begin(), safeText.end(), '\r'),
		safeText.end());
	safeText.erase(std::remove(safeText.begin(), safeText.end(), '\n'),
		safeText.end());
	std::size_t available = MAX_LINE_LENGTH - prefix.size();
	if (safeText.size() > available)
		safeText.erase(available);
	return prefix + safeText + "\r\n";
}

void Server::numeric(Client &client, int code, const std::string &params)
{
	std::ostringstream number;
	number.width(3);
	number.fill('0');
	number << code;
	std::string prefix = ":" + std::string(SERVER_NAME) + " " + number.str()
		+ " " + nicknameOrStar(client) + " ";
	if (prefix.size() > MAX_LINE_LENGTH)
	{
		std::cerr << "ircserv: unable to build numeric reply for client "
			<< client.fd << std::endl;
		return;
	}
	std::size_t available = MAX_LINE_LENGTH - prefix.size();
	std::string boundedParams = params;
	boundedParams.erase(std::remove(boundedParams.begin(), boundedParams.end(),
		'\r'), boundedParams.end());
	boundedParams.erase(std::remove(boundedParams.begin(), boundedParams.end(),
		'\n'), boundedParams.end());
	if (boundedParams.size() > available)
	{
		std::string::size_type trailing = boundedParams.find(" :");
		if (trailing == std::string::npos || trailing + 2 > available)
		{
			std::cerr << "ircserv: rejected oversized numeric reply for client "
				<< client.fd << std::endl;
			return;
		}
		boundedParams.erase(available);
	}
	queue(client, prefix + boundedParams + "\r\n");
}

void Server::sendToChannel(const Channel &channel, const std::string &message,
	int exceptFd)
{
	if (message.empty())
		return;
	for (std::map<int, bool>::const_iterator it = channel.members.begin();
		 it != channel.members.end(); ++it)
	{
		if (it->first == exceptFd)
			continue;
		std::map<int, Client>::iterator client = clients_.find(it->first);
		if (client != clients_.end() && !client->second.closing)
			queue(client->second, message);
	}
}

void Server::closeClient(int fd, const std::string &reason)
{
	std::map<int, Client>::iterator client = clients_.find(fd);
	if (client == clients_.end())
		return;

	std::set<int> recipients;
	for (std::map<std::string, Channel>::iterator channel = channels_.begin();
		 channel != channels_.end();)
	{
		if (client->second.registered && channel->second.hasMember(fd))
		{
			for (std::map<int, bool>::const_iterator member =
				 channel->second.members.begin();
				 member != channel->second.members.end(); ++member)
			{
				if (member->first != fd)
					recipients.insert(member->first);
			}
		}
		channel->second.members.erase(fd);
		channel->second.invitations.erase(fd);
		if (channel->second.members.empty())
		{
			std::map<std::string, Channel>::iterator removed = channel++;
			channels_.erase(removed);
		}
		else
			++channel;
	}

	if (client->second.registered)
	{
		std::string message = makeTrailingLine(clientPrefix(client->second)
			+ " QUIT :", reason.empty() ? "Client Quit" : reason);
		for (std::set<int>::const_iterator recipient = recipients.begin();
			 recipient != recipients.end(); ++recipient)
		{
			std::map<int, Client>::iterator target = clients_.find(*recipient);
			if (target != clients_.end())
				queue(target->second, message);
		}
	}
	close(fd);
	clients_.erase(client);
}

void Server::removeFromChannel(int fd, const std::string &channelName,
	const std::string &message)
{
	std::map<std::string, Channel>::iterator channel =
		channels_.find(caseFold(channelName));
	if (channel == channels_.end())
		return;
	sendToChannel(channel->second, message, -1);
	channel->second.members.erase(fd);
	channel->second.invitations.erase(fd);
	if (channel->second.members.empty())
		channels_.erase(channel);
}

void Server::sendNames(Client &client, const Channel &channel)
{
	std::string prefix = ":" + std::string(SERVER_NAME) + " 353 "
		+ nicknameOrStar(client) + " = " + channel.name + " :";
	std::size_t available = prefix.size() < MAX_LINE_LENGTH
		? MAX_LINE_LENGTH - prefix.size() : 0;
	std::string names;
	for (std::map<int, bool>::const_iterator member = channel.members.begin();
		 member != channel.members.end(); ++member)
	{
		std::map<int, Client>::const_iterator user = clients_.find(member->first);
		if (user == clients_.end())
			continue;
		std::string item = (member->second ? "@" : "")
			+ user->second.nickname;
		std::size_t separator = names.empty() ? 0 : 1;
		if (!names.empty() && names.size() + separator + item.size() > available)
		{
			queue(client, prefix + names + "\r\n");
			names.clear();
			separator = 0;
		}
		if (item.size() + separator <= available)
		{
			if (separator != 0)
				names += " ";
			names += item;
		}
	}
	if (!names.empty())
		queue(client, prefix + names + "\r\n");
	numeric(client, 366, channel.name + " :End of /NAMES list");
}

bool Server::validNickname(const std::string &nickname) const
{
	if (nickname.empty() || nickname.size() > 30)
		return false;
	const std::string firstAllowed =
		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ[]\\`_^{|}";
	const std::string otherAllowed = firstAllowed
		+ "0123456789-";
	if (firstAllowed.find(nickname[0]) == std::string::npos)
		return false;
	for (std::string::size_type i = 1; i < nickname.size(); ++i)
	{
		if (otherAllowed.find(nickname[i]) == std::string::npos)
			return false;
	}
	return true;
}

bool Server::validChannelName(const std::string &name) const
{
	if (name.size() < 2 || name.size() > 50
		|| (name[0] != '#' && name[0] != '&'))
		return false;
	for (std::string::size_type i = 1; i < name.size(); ++i)
	{
		unsigned char character = static_cast<unsigned char>(name[i]);
		if (character <= 32 || character == 127 || name[i] == ','
			|| name[i] == ':')
			return false;
	}
	return true;
}

bool Server::parseLimit(const std::string &text, unsigned long &value) const
{
	if (text.empty())
		return false;
	for (std::string::size_type i = 0; i < text.size(); ++i)
	{
		if (!std::isdigit(static_cast<unsigned char>(text[i])))
			return false;
	}
	char *end = NULL;
	errno = 0;
	unsigned long parsed = std::strtoul(text.c_str(), &end, 10);
	if (end == text.c_str() || *end != '\0' || errno == ERANGE || parsed == 0)
		return false;
	value = parsed;
	return true;
}

Channel *Server::findChannel(const std::string &name)
{
	std::map<std::string, Channel>::iterator it = channels_.find(caseFold(name));
	return it == channels_.end() ? NULL : &it->second;
}

Client *Server::findNickname(const std::string &nickname)
{
	for (std::map<int, Client>::iterator it = clients_.begin();
		 it != clients_.end(); ++it)
	{
		if (caseFold(it->second.nickname) == caseFold(nickname))
			return &it->second;
	}
	return NULL;
}

std::string Server::clientPrefix(const Client &client) const
{
	return ":" + client.nickname + "!" + client.username + "@localhost";
}

std::string Server::nicknameOrStar(const Client &client) const
{
	return client.nickname.empty() ? "*" : client.nickname;
}

std::string Server::upper(const std::string &text) const
{
	std::string result = text;
	for (std::string::size_type i = 0; i < result.size(); ++i)
		result[i] = static_cast<char>(
			std::toupper(static_cast<unsigned char>(result[i])));
	return result;
}

std::string Server::caseFold(const std::string &text) const
{
	std::string result = text;
	for (std::string::size_type i = 0; i < result.size(); ++i)
	{
		if (result[i] >= 'A' && result[i] <= 'Z')
			result[i] = static_cast<char>(result[i] - 'A' + 'a');
		else if (result[i] == '[')
			result[i] = '{';
		else if (result[i] == ']')
			result[i] = '}';
		else if (result[i] == '\\')
			result[i] = '|';
		else if (result[i] == '^')
			result[i] = '~';
	}
	return result;
}

std::vector<std::string> Server::split(const std::string &text,
	char delimiter) const
{
	std::vector<std::string> result;
	std::string::size_type start = 0;
	while (start <= text.size())
	{
		std::string::size_type end = text.find(delimiter, start);
		std::string item = text.substr(start,
			end == std::string::npos ? std::string::npos : end - start);
		if (!item.empty())
			result.push_back(item);
		if (end == std::string::npos)
			break;
		start = end + 1;
	}
	return result;
}

void Server::handleJoin(Client &client, const std::vector<std::string> &params)
{
	if (params.empty())
	{
		numeric(client, 461, "JOIN :Not enough parameters");
		return;
	}
	if (params[0] == "0")
	{
		std::vector<std::string> joined;
		for (std::map<std::string, Channel>::const_iterator channel =
			 channels_.begin(); channel != channels_.end(); ++channel)
		{
			if (channel->second.hasMember(client.fd))
				joined.push_back(channel->second.name);
		}
		for (std::size_t i = 0; i < joined.size(); ++i)
			removeFromChannel(client.fd, joined[i], makeTrailingLine(
				clientPrefix(client) + " PART " + joined[i] + " :",
				"Leaving all channels"));
		return;
	}
	std::vector<std::string> names = splitPreservingEmpty(params[0], ',');
	std::vector<std::string> keys;
	if (params.size() > 1)
		keys = splitPreservingEmpty(params[1], ',');
	for (std::size_t i = 0; i < names.size(); ++i)
	{
		if (names[i].empty())
		{
			numeric(client, 403, ":No such channel");
			continue;
		}
		if (!validChannelName(names[i]))
		{
			numeric(client, 403, names[i] + " :No such channel");
			continue;
		}
		std::string channelKey = caseFold(names[i]);
		std::map<std::string, Channel>::iterator found = channels_.find(channelKey);
		bool created = found == channels_.end();
		if (created)
		{
			Channel channel;
			channel.name = names[i];
			found = channels_.insert(std::make_pair(channelKey, channel)).first;
		}
		Channel &channel = found->second;
		if (channel.hasMember(client.fd))
			continue;
		if (channel.inviteOnly && channel.invitations.find(client.fd)
			== channel.invitations.end())
		{
			numeric(client, 473, channel.name + " :Cannot join channel (+i)");
			continue;
		}
		std::string suppliedKey = i < keys.size() ? keys[i] : "";
		if (!channel.key.empty() && suppliedKey != channel.key)
		{
			numeric(client, 475, channel.name + " :Cannot join channel (+k)");
			continue;
		}
		if (channel.userLimit > 0 && channel.members.size() >= channel.userLimit)
		{
			numeric(client, 471, channel.name + " :Cannot join channel (+l)");
			continue;
		}
		channel.members[client.fd] = created;
		channel.invitations.erase(client.fd);
		sendToChannel(channel, makeTrailingLine(
			clientPrefix(client) + " JOIN :", channel.name), -1);
		if (channel.topic.empty())
			numeric(client, 331, channel.name + " :No topic is set");
		else
			numeric(client, 332, channel.name + " :" + channel.topic);
		sendNames(client, channel);
	}
}

void Server::handlePrivmsg(Client &client, const std::string &command,
	const std::vector<std::string> &params)
{
	bool notice = command == "NOTICE";
	if (params.empty())
	{
		if (!notice)
			numeric(client, 411, ":No recipient given (" + command + ")");
		return;
	}
	if (params.size() < 2 || params[1].empty())
	{
		if (!notice)
			numeric(client, 412, ":No text to send");
		return;
	}
	std::vector<std::string> targets = split(params[0], ',');
	if (targets.empty())
	{
		if (!notice)
			numeric(client, 411, ":No recipient given (PRIVMSG)");
		return;
	}
	std::set<std::string> seenTargets;
	for (std::size_t i = 0; i < targets.size(); ++i)
	{
		if (!seenTargets.insert(caseFold(targets[i])).second)
			continue;
		std::string prefix = clientPrefix(client) + " " + command + " "
			+ targets[i] + " :";
		if (prefix.size() >= MAX_LINE_LENGTH)
			continue;
		std::size_t available = MAX_LINE_LENGTH - prefix.size();
		std::string text = params[1];
		text.erase(std::remove(text.begin(), text.end(), '\r'), text.end());
		text.erase(std::remove(text.begin(), text.end(), '\n'), text.end());
		text = text.substr(0, available);
		if (text.empty())
			continue;
		std::string message = prefix + text + "\r\n";
		if (!targets[i].empty() && (targets[i][0] == '#' || targets[i][0] == '&'))
		{
			Channel *channel = findChannel(targets[i]);
			if (channel == NULL)
			{
				if (!notice)
					numeric(client, 403, targets[i] + " :No such channel");
				continue;
			}
			// Without channel mode +n, IRC permits messages from non-members.
			// This server does not implement +n, so do not block them.
			sendToChannel(*channel, message, client.fd);
			continue;
		}
		Client *recipient = findNickname(targets[i]);
		if (recipient == NULL || !recipient->registered || recipient->closing)
		{
			if (!notice)
				numeric(client, 401, targets[i] + " :No such nick");
			continue;
		}
		if (!notice && !recipient->awayMessage.empty())
			numeric(client, 301, recipient->nickname + " :"
				+ recipient->awayMessage);
		queue(*recipient, message);
	}
}

void Server::handleMode(Client &client, const std::vector<std::string> &params)
{
	if (params.empty())
	{
		numeric(client, 461, "MODE :Not enough parameters");
		return;
	}
	Channel *channel = findChannel(params[0]);
	if (channel == NULL)
	{
		numeric(client, 403, params[0] + " :No such channel");
		return;
	}
	if (params.size() == 1)
	{
		std::string modes = "+";
		if (channel->inviteOnly)
			modes += "i";
		if (channel->topicRestricted)
			modes += "t";
		if (!channel->key.empty())
			modes += "k";
		if (channel->userLimit > 0)
			modes += "l";
		std::string extra;
		if (!channel->key.empty())
			extra += " *";
		if (channel->userLimit > 0)
			extra += " " + numberString(channel->userLimit);
		numeric(client, 324, channel->name + " " + modes + extra);
		return;
	}
	if (!channel->hasMember(client.fd))
	{
		numeric(client, 442, channel->name + " :You are not on that channel");
		return;
	}
	if (!channel->isOperator(client.fd))
	{
		numeric(client, 482, channel->name + " :You are not channel operator");
		return;
	}
	std::string requestedModeLine = clientPrefix(client) + " MODE "
		+ channel->name + " " + params[1];
	for (std::size_t i = 2; i < params.size(); ++i)
		requestedModeLine += " " + params[i];
	if (requestedModeLine.size() > MAX_LINE_LENGTH)
	{
		numeric(client, 696, channel->name + " :Mode line is too long");
		return;
	}
	bool inviteOnly = channel->inviteOnly;
	bool topicRestricted = channel->topicRestricted;
	std::string channelKey = channel->key;
	unsigned long userLimit = channel->userLimit;
	std::map<int, bool> memberModes = channel->members;
	const std::string &modeText = params[1];
	bool adding = true;
	std::size_t argument = 2;
	char previousSign = '\0';
	std::string appliedModes;
	std::string modeArguments;
	for (std::string::size_type i = 0; i < modeText.size(); ++i)
	{
		char mode = modeText[i];
		if (mode == '+' || mode == '-')
		{
			adding = mode == '+';
			continue;
		}
		bool valid = true;
		bool invalidParameter = false;
		bool changed = false;
		std::string value;
		std::string modeArgument;
		if (mode == 'i')
		{
			changed = inviteOnly != adding;
			inviteOnly = adding;
		}
		else if (mode == 't')
		{
			changed = topicRestricted != adding;
			topicRestricted = adding;
		}
		else if (mode == 'k')
		{
			if (adding)
			{
				if (argument >= params.size())
					valid = false;
				else
				{
					value = params[argument++];
					if (value.empty())
					{
						valid = false;
						invalidParameter = true;
					}
					else
					{
						bool validKey = true;
						for (std::string::size_type j = 0; j < value.size(); ++j)
						{
							unsigned char character =
								static_cast<unsigned char>(value[j]);
							if (character <= 32 || character == 127
								|| value[j] == ',' || value[j] == ':')
							{
								validKey = false;
								break;
							}
						}
						if (!validKey)
						{
							valid = false;
							invalidParameter = true;
						}
						else
						{
							changed = channelKey != value;
							if (changed)
							{
								channelKey = value;
								modeArgument = value;
							}
						}
					}
				}
			}
			else if (!channelKey.empty())
			{
				channelKey.clear();
				changed = true;
			}
		}
		else if (mode == 'l')
		{
			if (adding)
			{
				unsigned long limit = 0;
				if (argument >= params.size())
					valid = false;
				else
				{
					value = params[argument++];
					if (!parseLimit(value, limit))
					{
						valid = false;
						invalidParameter = true;
					}
					else
					{
						changed = userLimit != limit;
						if (changed)
						{
							userLimit = limit;
							modeArgument = value;
						}
					}
				}
			}
			else if (userLimit > 0)
			{
				userLimit = 0;
				changed = true;
			}
		}
		else if (mode == 'o')
		{
			if (argument >= params.size())
				valid = false;
			else
			{
				value = params[argument++];
				Client *target = findNickname(value);
				if (target == NULL || target->closing)
				{
					numeric(client, 401, value + " :No such nick");
					continue;
				}
				if (!channel->hasMember(target->fd))
				{
					numeric(client, 441, value + " " + channel->name
						+ " :They aren't on that channel");
					continue;
				}
				std::map<int, bool>::iterator member =
					memberModes.find(target->fd);
				if (member->second != adding)
				{
					member->second = adding;
					modeArgument = value;
					changed = true;
				}
			}
		}
		else
		{
			numeric(client, 472, std::string(1, mode)
				+ " :is unknown mode char to me");
			continue;
		}
		if (!valid)
		{
			if (invalidParameter)
			{
				std::string errorParams = channel->name + " "
					+ std::string(1, mode);
				if (!value.empty())
					errorParams += " " + value;
				numeric(client, 696, errorParams + " :Invalid mode parameter");
			}
			else
				numeric(client, 461, "MODE :Not enough parameters");
			continue;
		}
		if (!changed)
			continue;
		if (previousSign != (adding ? '+' : '-'))
		{
			appliedModes += adding ? "+" : "-";
			previousSign = adding ? '+' : '-';
		}
		appliedModes += mode;
		if (!modeArgument.empty())
			modeArguments += " " + modeArgument;
	}
	if (!appliedModes.empty())
	{
		std::string message = clientPrefix(client) + " MODE "
			+ channel->name + " " + appliedModes + modeArguments + "\r\n";
		if (message.size() > MAX_LINE_LENGTH + 2)
		{
			numeric(client, 696, channel->name + " :Mode line is too long");
			return;
		}
		channel->inviteOnly = inviteOnly;
		channel->topicRestricted = topicRestricted;
		channel->key = channelKey;
		channel->userLimit = userLimit;
		channel->members.swap(memberModes);
		sendToChannel(*channel, message, -1);
	}
}

void Server::handleWho(Client &client, const std::vector<std::string> &params)
{
	if (params.empty() || params[0] == "*")
	{
		for (std::map<int, Client>::const_iterator user = clients_.begin();
			 user != clients_.end(); ++user)
		{
			if (!user->second.registered)
				continue;
			numeric(client, 352, "* " + user->second.username
				+ " localhost ircserv.local " + user->second.nickname
				+ (user->second.awayMessage.empty() ? " H" : " G")
				+ " :0 " + user->second.realname);
		}
		std::string mask = params.empty() ? "*" : params[0];
		numeric(client, 315, mask + " :End of /WHO list");
		return;
	}
	Channel *channel = findChannel(params[0]);
	if (channel != NULL)
	{
		for (std::map<int, bool>::const_iterator member = channel->members.begin();
			 member != channel->members.end(); ++member)
		{
			std::map<int, Client>::const_iterator user = clients_.find(member->first);
			if (user == clients_.end() || !user->second.registered)
				continue;
			numeric(client, 352, channel->name + " " + user->second.username
				+ " localhost ircserv.local " + user->second.nickname
				+ (user->second.awayMessage.empty() ? " H" : " G")
				+ (member->second ? "@" : "") + " :0 "
				+ user->second.realname);
		}
	}
	else
	{
		Client *user = findNickname(params[0]);
		if (user != NULL && user->registered)
			numeric(client, 352, "* " + user->username
				+ " localhost ircserv.local " + user->nickname
				+ (user->awayMessage.empty() ? " H :0 " : " G :0 ")
				+ user->realname);
	}
	numeric(client, 315, params[0] + " :End of /WHO list");
}

void Server::handleWhois(Client &client, const std::vector<std::string> &params)
{
	if (params.empty())
	{
		numeric(client, 431, ":No nickname given");
		return;
	}
	std::string nicknameList = params.size() > 1 ? params[1] : params[0];
	std::vector<std::string> nicknames = split(nicknameList, ',');
	if (nicknames.empty())
	{
		numeric(client, 431, ":No nickname given");
		return;
	}
	for (std::size_t i = 0; i < nicknames.size(); ++i)
	{
		Client *user = findNickname(nicknames[i]);
		if (user == NULL || !user->registered)
		{
			numeric(client, 401, nicknames[i] + " :No such nick");
			numeric(client, 318, nicknames[i] + " :End of /WHOIS list");
			continue;
		}
		numeric(client, 311, user->nickname + " " + user->username
			+ " localhost * :" + user->realname);
		if (!user->awayMessage.empty())
			numeric(client, 301, user->nickname + " :" + user->awayMessage);
		std::string channelNames;
		std::string namesPrefix = user->nickname + " :";
		std::string numericPrefix = ":" + std::string(SERVER_NAME) + " 319 "
			+ nicknameOrStar(client) + " ";
		std::size_t available = MAX_LINE_LENGTH - numericPrefix.size()
			- namesPrefix.size();
		for (std::map<std::string, Channel>::const_iterator channel =
			 channels_.begin(); channel != channels_.end(); ++channel)
		{
			if (!channel->second.hasMember(user->fd))
				continue;
			std::string item = (channel->second.isOperator(user->fd) ? "@" : "")
				+ channel->second.name;
			std::size_t separator = channelNames.empty() ? 0 : 1;
			if (!channelNames.empty()
				&& channelNames.size() + separator + item.size() > available)
			{
				numeric(client, 319, namesPrefix + channelNames);
				channelNames.clear();
				separator = 0;
			}
			if (item.size() + separator <= available)
			{
				if (separator != 0)
					channelNames += " ";
				channelNames += item;
			}
		}
		if (!channelNames.empty())
			numeric(client, 319, namesPrefix + channelNames);
		numeric(client, 312, user->nickname + " ircserv.local :ft_irc server");
		numeric(client, 318, user->nickname + " :End of /WHOIS list");
	}
}
