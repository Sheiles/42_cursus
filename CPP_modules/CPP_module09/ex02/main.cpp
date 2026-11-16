#include "PmergeMe.hpp"

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <deque>

namespace
{
	bool parseNumber(const char *text, unsigned int &value)
	{
		if (text == NULL || *text == '\0')
			return false;
		for (const char *current = text; *current != '\0'; ++current)
		{
			if (*current < '0' || *current > '9')
				return false;
		}
		errno = 0;
		unsigned long parsed = std::strtoul(text, NULL, 10);
		if (errno == ERANGE || parsed == 0 || parsed > UINT_MAX)
			return false;
		value = static_cast<unsigned int>(parsed);
		return true;
	}

	void printValues(const std::vector<unsigned int> &values)
	{
		for (std::size_t i = 0; i < values.size(); ++i)
		{
			if (i != 0)
				std::cout << ' ';
			std::cout << values[i];
		}
		std::cout << std::endl;
	}
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: expected a sequence of positive integers." << std::endl;
		return 1;
	}

	std::vector<unsigned int> inputValues;
	for (int i = 1; i < argc; ++i)
	{
		unsigned int value = 0;
		if (!parseNumber(argv[i], value))
		{
			std::cerr << "Error: invalid positive integer." << std::endl;
			return 1;
		}
		inputValues.push_back(value);
	}

	std::cout << "Before: ";
	printValues(inputValues);

	PmergeMe sorter;
	std::clock_t start = std::clock();
	std::vector<unsigned int> vectorValues;
	for (std::size_t i = 0; i < inputValues.size(); ++i)
		vectorValues.push_back(inputValues[i]);
	sorter.sortVector(vectorValues);
	std::clock_t finish = std::clock();
	double vectorTime = 1000000.0 * (finish - start) / CLOCKS_PER_SEC;

	start = std::clock();
	std::deque<unsigned int> dequeValues;
	for (std::size_t i = 0; i < inputValues.size(); ++i)
		dequeValues.push_back(inputValues[i]);
	sorter.sortDeque(dequeValues);
	finish = std::clock();
	double dequeTime = 1000000.0 * (finish - start) / CLOCKS_PER_SEC;

	std::cout << "After: ";
	printValues(vectorValues);
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << vectorValues.size()
		<< " elements with std::vector: " << vectorTime << " us" << std::endl;
	std::cout << "Time to process a range of " << dequeValues.size()
		<< " elements with std::deque: " << dequeTime << " us" << std::endl;
	return 0;
}
