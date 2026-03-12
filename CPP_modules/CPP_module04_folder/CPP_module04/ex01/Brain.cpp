#include "Brain.hpp"
#include <iostream>

Brain::Brain(void)
{
	std::cout << "Brain constructor called" << std::endl;
}

Brain::Brain(const Brain &copy)
{
	std::cout << "Brain copy constructor called" << std::endl;
	int i = 0;
	while (i < 100)
	{
		this->ideas[i] = copy.ideas[i];
		i++;
	}
}

Brain &Brain::operator=(const Brain &rhs)
{
	std::cout << "Brain copy assignment operator called" << std::endl;
	if (this != &rhs)
	{
		int i = 0;
		while (i < 100)
		{
			this->ideas[i] = rhs.ideas[i];
			i++;
		}
	}
	return *this;
}

Brain::~Brain(void)
{
	std::cout << "Brain destructor called" << std::endl;
}
