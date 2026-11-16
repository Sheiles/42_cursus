#include "BitcoinExchange.hpp"

#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}

	BitcoinExchange exchange;
	if (!exchange.loadDatabase())
		return 1;
	return exchange.processInput(argv[1]) ? 0 : 1;
}
