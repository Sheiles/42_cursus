#include "Cat.hpp"

Cat::Cat(void)
{
	this->type = "Cat";
	std::cout << "Cat constructor called" << std::endl;
}

Cat::Cat(const Cat &copy) : Animal(copy)
{
	std::cout << "Cat copy constructor called" << std::endl;
}

Cat &Cat::operator=(const Cat &rhs)
{
	std::cout << "Cat copy assignment operator called" << std::endl;
	Animal::operator=(rhs);
	return *this;
}

Cat::~Cat(void)
{
	std::cout << "Cat destructor called" << std::endl;
}

void Cat::makeSound(void) const
{
	std::cout << "Meow! Meow!" << std::endl;
}
