#include "PhoneBook.hpp"
#include "Contact.hpp"
#include <iostream>
#include <string>
#include <sstream>

static bool readLine(const std::string &prompt, std::string &out)
{
	std::cout << prompt;
	if (!std::getline(std::cin, out))
		return false;
	return true;
}

static std::string readNonEmptyField(const std::string &prompt)
{
	std::string s;
	while (true)
	{
		if (!readLine(prompt, s))
			return std::string(); // EOF => renvoie vide, main gérera
		if (!s.empty())
			return s;
		std::cout << "Field cannot be empty." << std::endl;
	}
}

static bool isDigitsSpacesPlus(const std::string &s)
{
	// optionnel : accepte chiffres, espaces, +, -, (), .
	// (les règles ne l'exigent pas, mais ça évite n'importe quoi)
	for (std::string::size_type i = 0; i < s.size(); ++i)
	{
		char c = s[i];
		if ((c >= '0' && c <= '9') || c == ' ' || c == '+' || c == '-' || c == '(' || c == ')' || c == '.')
			continue;
		return false;
	}
	return !s.empty();
}

static std::string readPhone(const std::string &prompt)
{
	std::string s;
	while (true)
	{
		if (!readLine(prompt, s))
			return std::string();
		if (!s.empty() && isDigitsSpacesPlus(s))
			return s;
		std::cout << "Invalid phone number (use digits and common symbols)." << std::endl;
	}
}

static int parseIndex1to8(const std::string &s)
{
	std::istringstream iss(s);
	int x;
	char extra;
	if (!(iss >> x))
		return -1;
	if (iss >> extra)
		return -1;
	if (x < 1 || x > 8)
		return -1;
	return x;
}

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
		else if (cmd == "ADD")
		{
			Contact c;

			std::string fn = readNonEmptyField("First name: ");
			if (std::cin.eof()) break;
			std::string ln = readNonEmptyField("Last name: ");
			if (std::cin.eof()) break;
			std::string nn = readNonEmptyField("Nickname: ");
			if (std::cin.eof()) break;
			std::string pn = readPhone("Phone number: ");
			if (std::cin.eof()) break;
			std::string ds = readNonEmptyField("Darkest secret: ");
			if (std::cin.eof()) break;

			c.setFirstName(fn);
			c.setLastName(ln);
			c.setNickname(nn);
			c.setPhoneNumber(pn);
			c.setDarkestSecret(ds);

			pb.addContact(c);
			std::cout << "Contact saved." << std::endl;
		}
		else if (cmd == "SEARCH")
		{
			if (pb.count() == 0)
			{
				std::cout << "PhoneBook is empty." << std::endl;
				continue;
			}
			pb.printTable();

			std::string idxStr;
			std::cout << "Enter index to display: ";
			if (!std::getline(std::cin, idxStr))
				break;

			int idx = parseIndex1to8(idxStr);
			if (idx == -1)
				std::cout << "Invalid index." << std::endl;
			else
				pb.printContact(idx - 1);
		}
		else
		{
			// input ignoré
			continue;
		}
	}
	return 0;
}
