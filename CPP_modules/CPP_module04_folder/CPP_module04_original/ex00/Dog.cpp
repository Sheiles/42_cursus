#include "Dog.hpp"

Dog::Dog(void)
{
	this->type = "Dog";
	std::cout << "Dog constructor called" << std::endl;
}

Dog::Dog(const Dog &copy) : Animal(copy)
{
	std::cout << "Dog copy constructor called" << std::endl;
}

Dog &Dog::operator=(const Dog &rhs)
{
	std::cout << "Dog copy assignment operator called" << std::endl;
	Animal::operator=(rhs);
	return *this;
}

Dog::~Dog(void)
{
	std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound(void) const
{
	std::cout << "Woof! Woof!" << std::endl;
}
