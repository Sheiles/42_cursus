#include "AAnimal.hpp"

AAnimal::AAnimal(void) : type("")
{
	std::cout << "AAnimal constructor called" << std::endl;
}

AAnimal::AAnimal(const AAnimal &copy) : type(copy.type)
{
	std::cout << "AAnimal copy constructor called" << std::endl;
}

AAnimal &AAnimal::operator=(const AAnimal &rhs)
{
	std::cout << "AAnimal copy assignment operator called" << std::endl;
	if (this != &rhs)
		this->type = rhs.type;
	return *this;
}

AAnimal::~AAnimal(void)
{
	std::cout << "AAnimal destructor called" << std::endl;
}

std::string AAnimal::getType(void) const
{
	return this->type;
}
