#include "easyfind.hpp"

#include <iostream>
#include <list>
#include <vector>

int main()
{
	std::vector<int> values;
	values.push_back(4);
	values.push_back(9);
	values.push_back(9);

	try
	{
		std::vector<int>::iterator found = easyfind(values, 9);
		std::cout << "first match: " << (found - values.begin()) << std::endl;

		const std::vector<int> constValues(values);
		std::vector<int>::const_iterator constFound = easyfind(constValues, 4);
		std::cout << "const match: " << *constFound << std::endl;

		std::list<int> linkedValues;
		linkedValues.push_back(12);
		linkedValues.push_back(7);
		std::cout << "list match: " << *easyfind(linkedValues, 7) << std::endl;

		easyfind(values, 42);
	}
	catch (const std::exception &error)
	{
		std::cout << "not found: " << error.what() << std::endl;
	}

	std::vector<int> emptyValues;
	try
	{
		easyfind(emptyValues, 42);
	}
	catch (const std::exception &error)
	{
		std::cout << "empty container: " << error.what() << std::endl;
	}
	return 0;
}
