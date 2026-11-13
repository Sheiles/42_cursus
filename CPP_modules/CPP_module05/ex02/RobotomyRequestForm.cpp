#include "RobotomyRequestForm.hpp"

#include <cstdlib>
#include <iostream>

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
	: AForm("RobotomyRequestForm", 72, 45), _target(target)
{
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other)
	: AForm(other), _target(other._target)
{
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

RobotomyRequestForm &RobotomyRequestForm::operator=(
	const RobotomyRequestForm &other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return (*this);
}

const std::string &RobotomyRequestForm::get_target() const
{
	return (_target);
}

void RobotomyRequestForm::execute_action() const
{
	std::cout << "Brrrrrrr... drilling noises..." << std::endl;
	if (std::rand() % 2 == 0)
	{
		std::cout << _target << " has been robotomized successfully."
			<< std::endl;
	}
	else
	{
		std::cout << "Robotomy of " << _target << " failed." << std::endl;
	}
}
