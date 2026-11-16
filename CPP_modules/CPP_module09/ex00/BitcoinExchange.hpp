#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange
{
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);
	~BitcoinExchange();

	bool loadDatabase();
	bool processInput(const std::string &filename) const;

private:
	std::map<std::string, double> _rates;

	bool isValidDate(const std::string &date) const;
	void processLine(const std::string &line) const;
};

#endif
