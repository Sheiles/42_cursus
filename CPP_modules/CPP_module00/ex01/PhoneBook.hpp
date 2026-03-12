#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

class PhoneBook
{
private:
	Contact _contacts[8];
	int     _count;      
	int     _nextIndex;  

public:
	PhoneBook();
	~PhoneBook();

	void addContact(const Contact &c);
	void printTable() const;
	void printContact(int index) const;

	int  count() const;
};

#endif
