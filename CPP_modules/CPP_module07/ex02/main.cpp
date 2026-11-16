#include "Array.hpp"

#include <iostream>
#include <string>

int main()
{
	Array<int> numbers(3);
	std::cout << "size = " << numbers.size() << std::endl;
	std::cout << "default value = " << numbers[0] << std::endl;

	numbers[0] = 10;
	numbers[1] = 20;
	numbers[2] = 30;

	Array<int> copy(numbers);
	copy[0] = 99;
	std::cout << "original[0] = " << numbers[0] << std::endl;
	std::cout << "copy[0] = " << copy[0] << std::endl;

	Array<int> assigned;
	assigned = numbers;
	assigned[1] = 77;
	std::cout << "original[1] = " << numbers[1] << std::endl;
	std::cout << "assigned[1] = " << assigned[1] << std::endl;

	Array<std::string> words(2);
	words[0] = "templates";
	words[1] = "work";
	const Array<std::string> &constantWords = words;
	std::cout << constantWords[0] << " " << constantWords[1] << std::endl;

	try
	{
		numbers[-2] = 0;
	}
	catch (const std::exception &error)
	{
		std::cout << error.what() << std::endl;
	}

	try
	{
		numbers[numbers.size()] = 0;
	}
	catch (const std::exception &error)
	{
		std::cout << error.what() << std::endl;
	}

	return 0;
}
