#include "PhoneBook.hpp"
#include "PhoneBookApp.hpp"
#include <iostream>
#include <string>

int main()
{
	PhoneBook pb;
	std::string cmd;
	while (true)
	{
		std::cout << "Enter command (ADD, SEARCH, EXIT): ";
		if (!std::getline(std::cin, cmd))
			break;
		if (cmd == "EXIT")
			break;
		if (cmd == "ADD" && !handleAdd(pb))
			break;
		if (cmd == "SEARCH" && !handleSearch(pb))
			break;
	}
	return 0;
}
