#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main(void)
{
	std::cout << "=== Creating animals ===" << std::endl;
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	std::cout << "\n=== Array of animals ===" << std::endl;
	const Animal* animals[4];
	animals[0] = new Dog();
	animals[1] = new Cat();
	animals[2] = new Dog();
	animals[3] = new Cat();

	std::cout << "\n=== Making sounds ===" << std::endl;
	for (int k = 0; k < 4; k++)
		animals[k]->makeSound();

	std::cout << "\n=== Deletion ===" << std::endl;
	delete j;
	delete i;
	for (int k = 0; k < 4; k++)
		delete animals[k];

	return 0;
}
