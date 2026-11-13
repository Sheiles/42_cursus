#include "identify.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
	Base *object;

	std::srand(static_cast<unsigned int>(std::time(0)));
	for (int index = 0; index < 6; ++index)
	{
		object = generate();
		std::cout << "Pointer: ";
		identify(object);
		std::cout << "Reference: ";
		identify(*object);
		delete object;
	}
	return (0);
}
