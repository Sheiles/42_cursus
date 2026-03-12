#include "PhoneBookApp.hpp"
#include "Contact.hpp"
#include <iostream>
#include <sstream>
#include <string>

std::string readNonEmptyField(const std::string &prompt);
std::string readPhone(const std::string &prompt);

static int parseIndex1to8(const std::string &s)
{
	std::istringstream iss(s);
	int x;
	char extra;
	if (!(iss >> x) || (iss >> extra))
		return -1;
	if (x < 1 || x > 8)
		return -1;
	return x;
}

static bool fillContact(Contact &c)
{
	std::string fields[5] = {
		readNonEmptyField("First name: "),
		readNonEmptyField("Last name: "),
		readNonEmptyField("Nickname: "),
		readPhone("Phone number: "),
		readNonEmptyField("Darkest secret: ")
	};
	if (std::cin.eof())
		return false;
	c.setFirstName(fields[0]);
	c.setLastName(fields[1]);
	c.setNickname(fields[2]);
	c.setPhoneNumber(fields[3]);
	c.setDarkestSecret(fields[4]);
	return true;
}

bool handleAdd(PhoneBook &pb)
{
	Contact c;
	if (!fillContact(c))
		return false;
	pb.addContact(c);
	std::cout << "Contact saved." << std::endl;
	return true;
}

bool handleSearch(PhoneBook &pb)
{
	std::string idxStr;
	if (pb.count() == 0)
		return (std::cout << "PhoneBook is empty." << std::endl, true);
	pb.printTable();
	std::cout << "Enter index to display: ";
	if (!std::getline(std::cin, idxStr))
		return false;
	int idx = parseIndex1to8(idxStr);
	if (idx == -1)
		std::cout << "Invalid index." << std::endl;
	else
		pb.printContact(idx - 1);
	return true;
}