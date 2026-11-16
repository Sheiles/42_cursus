#include "BitcoinExchange.hpp"

#include <cfloat>
#include <cerrno>
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace
{
	std::string trim(const std::string &value)
	{
		std::string::size_type first = value.find_first_not_of(" \t\r\n");
		if (first == std::string::npos)
			return "";
		std::string::size_type last = value.find_last_not_of(" \t\r\n");
		return value.substr(first, last - first + 1);
	}

	bool isDecimalNumber(const std::string &text)
	{
		if (text.empty())
			return false;
		std::string::size_type i = 0;
		if (text[i] == '+' || text[i] == '-')
			++i;

		std::string::size_type digits = 0;
		while (i < text.size() && text[i] >= '0' && text[i] <= '9')
		{
			++digits;
			++i;
		}
		if (i < text.size() && text[i] == '.')
		{
			++i;
			while (i < text.size() && text[i] >= '0' && text[i] <= '9')
			{
				++digits;
				++i;
			}
		}
		if (digits == 0)
			return false;
		if (i < text.size() && (text[i] == 'e' || text[i] == 'E'))
		{
			++i;
			if (i < text.size() && (text[i] == '+' || text[i] == '-'))
				++i;
			std::string::size_type exponentDigits = 0;
			while (i < text.size() && text[i] >= '0' && text[i] <= '9')
			{
				++exponentDigits;
				++i;
			}
			if (exponentDigits == 0)
				return false;
		}
		return i == text.size();
	}

	bool parseNumber(const std::string &text, double &number)
	{
		if (!isDecimalNumber(text))
			return false;
		char *end = NULL;
		errno = 0;
		number = std::strtod(text.c_str(), &end);
		return end != text.c_str() && *end == '\0' && errno != ERANGE
			&& number == number && number <= DBL_MAX && number >= -DBL_MAX;
	}
}

BitcoinExchange::BitcoinExchange() : _rates()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
	: _rates(other._rates)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_rates = other._rates;
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	for (std::string::size_type i = 0; i < date.size(); ++i)
	{
		if (i != 4 && i != 7 && (date[i] < '0' || date[i] > '9'))
			return false;
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	if (year < 1 || month < 1 || month > 12)
		return false;
	const int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int days = monthDays[month - 1];
	if (month == 2 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)))
		days = 29;
	return day >= 1 && day <= days;
}

bool BitcoinExchange::loadDatabase()
{
	std::ifstream database("data.csv");
	if (!database.is_open())
	{
		database.clear();
		database.open("../data.csv");
	}
	if (!database.is_open())
	{
		std::cerr << "Error: could not open database." << std::endl;
		return false;
	}

	std::string line;
	if (!std::getline(database, line) || trim(line) != "date,exchange_rate")
	{
		std::cerr << "Error: invalid database header." << std::endl;
		return false;
	}
	while (std::getline(database, line))
	{
		std::string::size_type comma = line.find(',');
		if (comma == std::string::npos || line.find(',', comma + 1) != std::string::npos)
		{
			std::cerr << "Error: bad database input => " << line << std::endl;
			return false;
		}
		std::string date = trim(line.substr(0, comma));
		double rate = 0.0;
		if (!isValidDate(date) || !parseNumber(trim(line.substr(comma + 1)), rate)
			|| rate < 0.0)
		{
			std::cerr << "Error: bad database input => " << line << std::endl;
			return false;
		}
		_rates[date] = rate;
	}
	if (database.bad())
	{
		std::cerr << "Error: could not read database." << std::endl;
		return false;
	}
	if (_rates.empty())
	{
		std::cerr << "Error: database contains no exchange rates." << std::endl;
		return false;
	}
	return true;
}

bool BitcoinExchange::processInput(const std::string &filename) const
{
	std::ifstream input(filename.c_str());
	if (!input.is_open())
	{
		std::cout << "Error: could not open file." << std::endl;
		return false;
	}
	std::string line;
	bool firstLine = true;
	while (std::getline(input, line))
	{
		if (firstLine && trim(line) == "date | value")
		{
			firstLine = false;
			continue;
		}
		firstLine = false;
		processLine(line);
	}
	if (input.bad())
	{
		std::cerr << "Error: could not read input file." << std::endl;
		return false;
	}
	return true;
}

void BitcoinExchange::processLine(const std::string &line) const
{
	std::string::size_type separator = line.find('|');
	if (separator == std::string::npos
		|| line.find('|', separator + 1) != std::string::npos)
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}

	std::string date = trim(line.substr(0, separator));
	std::string valueText = trim(line.substr(separator + 1));
	if (!isValidDate(date))
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}
	double value = 0.0;
	if (!parseNumber(valueText, value))
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}
	if (value < 0.0)
	{
		std::cout << "Error: not a positive number." << std::endl;
		return;
	}
	if (value > 1000.0)
	{
		std::cout << "Error: too large a number." << std::endl;
		return;
	}

	std::map<std::string, double>::const_iterator rate = _rates.upper_bound(date);
	if (rate == _rates.begin())
	{
		std::cout << "Error: no earlier exchange rate available." << std::endl;
		return;
	}
	--rate;
	std::cout << date << " => " << value << " = " << value * rate->second << std::endl;
}
