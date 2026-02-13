#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

class PhoneBook
{
private:
	Contact _contacts[8];
	int     _count;      // nb contacts effectivement sauvegardés (0..8)
	int     _nextIndex;  // où écrire le prochain contact (0..7)

public:
	PhoneBook();
	~PhoneBook();

	void addContact(const Contact &c);
	void printTable() const;
	void printContact(int index) const;

	int  count() const;
};

#endif
