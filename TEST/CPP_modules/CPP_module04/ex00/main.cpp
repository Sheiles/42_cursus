#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main(void)
{
	std::cout << "=== Correct Polymorphism ===" << std::endl;
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	std::cout << "\nTypes:" << std::endl;
	std::cout << j->getType() << std::endl;
	std::cout << i->getType() << std::endl;

	std::cout << "\nSounds:" << std::endl;
	i->makeSound();
	j->makeSound();
	meta->makeSound();

	std::cout << "\nDeletion:" << std::endl;
	delete meta;
	delete j;
	delete i;

	std::cout << "\n=== Wrong Polymorphism ===" << std::endl;
	const WrongAnimal* wrong_meta = new WrongAnimal();
	const WrongAnimal* wrong_i = new WrongCat();

	std::cout << "\nTypes:" << std::endl;
	std::cout << wrong_i->getType() << std::endl;

	std::cout << "\nSounds:" << std::endl;
	wrong_i->makeSound();
	wrong_meta->makeSound();

	std::cout << "\nDeletion:" << std::endl;
	delete wrong_meta;
	delete wrong_i;

	return 0;
}
