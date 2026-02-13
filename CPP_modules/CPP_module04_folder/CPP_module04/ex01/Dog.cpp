#include "Dog.hpp"

Dog::Dog(void) : brain(new Brain())
{
	this->type = "Dog";
	std::cout << "Dog constructor called" << std::endl;
}

Dog::Dog(const Dog &copy) : Animal(copy), brain(new Brain(*copy.brain))
{
	std::cout << "Dog copy constructor called" << std::endl;
}

Dog &Dog::operator=(const Dog &rhs)
{
	std::cout << "Dog copy assignment operator called" << std::endl;
	if (this != &rhs)
	{
		Animal::operator=(rhs);
		delete this->brain;
		this->brain = new Brain(*rhs.brain);
	}
	return *this;
}

Dog::~Dog(void)
{
	delete this->brain;
	std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound(void) const
{
	std::cout << "Woof! Woof!" << std::endl;
}
