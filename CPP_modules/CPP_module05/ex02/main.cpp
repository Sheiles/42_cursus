#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#include <iostream>

static void test_shrubbery(Bureaucrat &executive,
	ShrubberyCreationForm &form)
{
	executive.executeForm(form);
	executive.signForm(form);
	executive.executeForm(form);
}

static void test_robotomy(Bureaucrat &executive, Bureaucrat &senior,
	RobotomyRequestForm &form)
{
	senior.signForm(form);
	senior.executeForm(form);
	executive.signForm(form);
	executive.executeForm(form);
}

static void test_pardon(Bureaucrat &executive,
	PresidentialPardonForm &form)
{
	executive.signForm(form);
	executive.executeForm(form);
}

int main()
{
	try
	{
		Bureaucrat executive("Executive", 1);
		Bureaucrat senior("Senior", 60);
		ShrubberyCreationForm shrubbery("garden");
		RobotomyRequestForm robotomy("Bender");
		PresidentialPardonForm pardon("Arthur Dent");

		test_shrubbery(executive, shrubbery);
		test_robotomy(executive, senior, robotomy);
		test_pardon(executive, pardon);
	}
	catch (const std::exception &error)
	{
		std::cout << "Caught exception: " << error.what() << std::endl;
		return (1);
	}
	return (0);
}
