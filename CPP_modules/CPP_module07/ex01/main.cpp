#include "iter.hpp"

#include <iostream>

void increment(int &value)
{
	++value;
}

template <typename T>
void printValue(const T &value)
{
	std::cout << value << std::endl;
}

int main()
{
	int values[] = {1, 2, 3};
	const char letters[] = {'a', 'b', 'c'};

	::iter(values, 3, increment);
	::iter(values, 3, printValue<int>);
	::iter(letters, 3, printValue<char>);

	return 0;
}
