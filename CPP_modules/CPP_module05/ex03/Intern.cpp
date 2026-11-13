#include "Intern.hpp"

#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#include <iostream>

Intern::Intern()
{
}

Intern::Intern(const Intern &other)
{
	(void)other;
}

Intern::~Intern()
{
}

Intern &Intern::operator=(const Intern &other)
{
	(void)other;
	return (*this);
}

AForm *Intern::makeForm(const std::string &form_name,
	const std::string &target) const
{
	AForm *form;

	form = NULL;
	if (form_name == "shrubbery creation")
	{
		form = new ShrubberyCreationForm(target);
	}
	else if (form_name == "robotomy request")
	{
		form = new RobotomyRequestForm(target);
	}
	else if (form_name == "presidential pardon")
	{
		form = new PresidentialPardonForm(target);
	}
	else
	{
		std::cout << "Intern: unknown form name '" << form_name << "'."
			<< std::endl;
		return (NULL);
	}
	std::cout << "Intern creates " << form_name << std::endl;
	return (form);
}
