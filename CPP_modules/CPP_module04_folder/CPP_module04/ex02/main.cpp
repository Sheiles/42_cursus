#include <iostream>
#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main(void)
{
	std::cout << "=== Creating abstract animals ===" << std::endl;
	// AAnimal cannot be instantiated
	// const AAnimal* abstract = new AAnimal(); // This would cause a compilation error

	const AAnimal* j = new Dog();
	const AAnimal* i = new Cat();

	std::cout << "\n=== Array of animals ===" << std::endl;
	const AAnimal* animals[4];
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
