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
