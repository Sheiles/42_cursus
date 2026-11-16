#include "Server.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

static bool validPort(const std::string &text)
{
	if (text.empty())
		return false;
	for (std::string::size_type i = 0; i < text.size(); ++i)
	{
		if (text[i] < '0' || text[i] > '9')
			return false;
	}
	char *end = NULL;
	long port = std::strtol(text.c_str(), &end, 10);
	return end != text.c_str() && *end == '\0' && port > 0 && port <= 65535;
}

int main(int argc, char **argv)
{
	if (argc != 3 || !validPort(argv[1]) || std::string(argv[2]).empty())
	{
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return 1;
	}
	try
	{
		Server server(argv[1], argv[2]);
		server.run();
	}
	catch (const std::exception &error)
	{
		std::cerr << "ircserv: " << error.what() << std::endl;
		return 1;
	}
	return 0;
}
