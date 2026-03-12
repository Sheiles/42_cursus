#include <iostream>
#include <string>

static bool readLine(const std::string &prompt, std::string &out)
{
	std::cout << prompt;
	if (!std::getline(std::cin, out))
		return false;
	return true;
}

std::string readNonEmptyField(const std::string &prompt)
{
	std::string s;
	while (true)
	{
		if (!readLine(prompt, s))
			return std::string();
		if (!s.empty())
			return s;
		std::cout << "Field cannot be empty." << std::endl;
	}
}

bool isDigitsSpacesPlus(const std::string &s)
{
	std::string::size_type i = 0;
	while (i < s.size())
	{
		char c = s[i];
		if ((c >= '0' && c <= '9') || c == ' ' || c == '+' || c == '-' || c == '(' || c == ')' || c == '.')
		{
			++i;
			continue;
		}
		return false;
	}
	return !s.empty();
}

std::string readPhone(const std::string &prompt)
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