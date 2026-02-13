#include "Animal.hpp"

Animal::Animal(void) : type("")
{
	std::cout << "Animal constructor called" << std::endl;
}

Animal::Animal(const Animal &copy) : type(copy.type)
{
	std::cout << "Animal copy constructor called" << std::endl;
}

Animal &Animal::operator=(const Animal &rhs)
{
	std::cout << "Animal copy assignment operator called" << std::endl;
	if (this != &rhs)
		this->type = rhs.type;
	return *this;
}

Animal::~Animal(void)
{
	std::cout << "Animal destructor called" << std::endl;
}

void Animal::makeSound(void) const
{
	std::cout << "Some animal sound..." << std::endl;
}

std::string Animal::getType(void) const
{
	return this->type;
}
