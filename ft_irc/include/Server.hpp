
#ifndef SERVER_HPP
#define SERVER_HPP

#include <map>
#include <set>
#include <string>
#include <ctime>
#include <vector>
#include <sys/types.h>

struct Client
{
	int fd;
	std::string nickname;
	std::string username;
	std::string realname;
	std::string awayMessage;
	std::string userModes;
	std::string closeReason;
	std::string input;
	std::string output;
	bool passwordAccepted;
	bool hasNickname;
	bool hasUser;
	bool capNegotiating;
	bool registered;
	bool closing;
	bool forceClose;
	std::time_t closeDeadline;

	Client();
};

struct Channel
{
	std::string name;
	std::string topic;
	std::string key;
	std::map<int, bool> members;
	std::set<int> invitations;
	bool inviteOnly;
	bool topicRestricted;
	unsigned long userLimit;

	Channel();
	bool hasMember(int fd) const;
	bool isOperator(int fd) const;
};

class Server
{
public:
	Server(const std::string &port, const std::string &password);
	~Server();
	void run();

private:
	enum IoResult
	{
		IO_PROGRESS,
		IO_DEFERRED, // Reassess on poll; fatal poll flags close the socket.
		IO_DISCONNECTED
	};

	int listener_;
	std::string port_;
	std::string password_;
	std::map<int, Client> clients_;
	std::map<std::string, Channel> channels_;

	Server(const Server &);
	Server &operator=(const Server &);

	void createListener(const std::string &port);
	void acceptClient();
	IoResult readClient(int fd);
	IoResult writeClient(int fd);
	void beginGracefulClose(Client &client, const std::string &reason);
	void closeReadyClients();
	void processInput(Client &client);
	void processLine(Client &client, const std::string &line);
	void processCommand(Client &client, const std::string &command,
		const std::vector<std::string> &params);
	void tryRegister(Client &client);

	void queue(Client &client, const std::string &message);
	std::string makeTrailingLine(const std::string &prefix,
		const std::string &text) const;
	void numeric(Client &client, int code, const std::string &params);
	void sendToChannel(const Channel &channel, const std::string &message,
		int exceptFd);
	void closeClient(int fd, const std::string &reason);
	void removeFromChannel(int fd, const std::string &channelName,
		const std::string &message);
	void sendNames(Client &client, const Channel &channel);

	bool validNickname(const std::string &nickname) const;
	bool validChannelName(const std::string &name) const;
	bool parseLimit(const std::string &text, unsigned long &value) const;
	Channel *findChannel(const std::string &name);
	Client *findNickname(const std::string &nickname);
	std::string clientPrefix(const Client &client) const;
	std::string nicknameOrStar(const Client &client) const;
	std::string upper(const std::string &text) const;
	std::string caseFold(const std::string &text) const;
	std::vector<std::string> split(const std::string &text, char delimiter) const;
	void handleJoin(Client &client, const std::vector<std::string> &params);
	void handlePrivmsg(Client &client, const std::string &command,
		const std::vector<std::string> &params);
	void handleMode(Client &client, const std::vector<std::string> &params);
	void handleWho(Client &client, const std::vector<std::string> &params);
	void handleWhois(Client &client, const std::vector<std::string> &params);
};

#endif
