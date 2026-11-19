#include "Intern.hpp"

#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#include <iostream>

namespace
{
	AForm *createShrubbery(const std::string &target)
	{
		return (new ShrubberyCreationForm(target));
	}

	AForm *createRobotomy(const std::string &target)
	{
		return (new RobotomyRequestForm(target));
	}

	AForm *createPardon(const std::string &target)
	{
		return (new PresidentialPardonForm(target));
	}

	struct FormFactory
	{
		const char *name;
		AForm *(*create)(const std::string &target);
	};
}

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
	const FormFactory factories[] = {
		{"shrubbery creation", &createShrubbery},
		{"robotomy request", &createRobotomy},
		{"presidential pardon", &createPardon}
	};
	const unsigned int count = sizeof(factories) / sizeof(factories[0]);

	for (unsigned int i = 0; i < count; ++i)
	{
		if (form_name == factories[i].name)
		{
			AForm *form = factories[i].create(target);
			std::cout << "Intern creates " << form_name << std::endl;
			return (form);
		}
	}
	std::cout << "Intern: unknown form name '" << form_name << "'."
		<< std::endl;
	return (NULL);
}