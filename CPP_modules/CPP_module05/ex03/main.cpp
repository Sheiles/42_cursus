#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"

#include <iostream>

static int run_known_form(Intern &intern)
{
	AForm *form;

	form = intern.makeForm("robotomy request", "Bender");
	if (form == NULL)
	{
		return (1);
	}

	try
	{
		Bureaucrat executive("Executive", 1);

		executive.signForm(*form);
		executive.executeForm(*form);
	}
	catch (const std::exception &error)
	{
		std::cout << "Caught exception: " << error.what() << std::endl;
		delete form;
		return (1);
	}
	delete form;
	return (0);
}

int main()
{
	Intern intern;

	if (run_known_form(intern) != 0)
	{
		return (1);
	}
	if (intern.makeForm("unknown form", "target") != NULL)
	{
		return (1);
	}
	return (0);
}
