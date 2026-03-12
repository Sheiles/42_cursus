#include <iostream>
#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main(void)
{
	std::cout << "=== Creating abstract animals ===" << std::endl;
	const AAnimal* j = new Dog();
	const AAnimal* i = new Cat();
	std::cout << "\n=== Array of animals ===" << std::endl;
	const AAnimal* animals[4] = {new Dog(), new Cat(), new Dog(), new Cat()};
	std::cout << "\n=== Making sounds ===" << std::endl;
	int k = 0;
	while (k < 4)
	{
		animals[k]->makeSound();
		k++;
	}
	std::cout << "\n=== Deletion ===" << std::endl;
	delete j;
	delete i;
	k = 0;
	while (k < 4)
	{
		delete animals[k];
		k++;
	}
	return 0;
}
