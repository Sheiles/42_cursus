#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <string>

PhoneBook::PhoneBook() : _count(0), _nextIndex(0) {}

PhoneBook::~PhoneBook() {}

void PhoneBook::addContact(const Contact &c)
{
	_contacts[_nextIndex] = c;
	_contacts[_nextIndex].markSet(true);

	_nextIndex = (_nextIndex + 1) % 8;
	if (_count < 8)
		_count++;
}

int PhoneBook::count() const { return _count; }

static std::string formatCell(const std::string &s)
{
	if (s.size() <= 10)
		return s;
	return s.substr(0, 9) + ".";
}

void PhoneBook::printTable() const
{
	std::cout << std::setw(10) << "index" << "|"
			  << std::setw(10) << "first name" << "|"
			  << std::setw(10) << "last name" << "|"
			  << std::setw(10) << "nickname" << std::endl;

	for (int i = 0; i < 8; ++i)
	{
		if (!_contacts[i].isSet())
			continue;

		std::cout << std::setw(10) << (i + 1) << "|"
				  << std::setw(10) << formatCell(_contacts[i].getFirstName()) << "|"
				  << std::setw(10) << formatCell(_contacts[i].getLastName()) << "|"
				  << std::setw(10) << formatCell(_contacts[i].getNickname())
				  << std::endl;
	}
}

void PhoneBook::printContact(int index) const
{
	if (index < 0 || index >= 8 || !_contacts[index].isSet())
	{
		std::cout << "Invalid index." << std::endl;
		return;
	}
	std::cout << "First name: " << _contacts[index].getFirstName() << std::endl;
	std::cout << "Last name: " << _contacts[index].getLastName() << std::endl;
	std::cout << "Nickname: " << _contacts[index].getNickname() << std::endl;
	std::cout << "Phone number: " << _contacts[index].getPhoneNumber() << std::endl;
	std::cout << "Darkest secret: " << _contacts[index].getDarkestSecret() << std::endl;
}
