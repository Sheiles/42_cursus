#include "Bureaucrat.hpp"
#include "Form.hpp"

#include <iostream>

int main()
{
	try
	{
		Form tax("Tax form", 50, 25);
		Bureaucrat intern("Intern", 100);
		Bureaucrat manager("Manager", 20);

		std::cout << tax << std::endl;
		intern.signForm(tax);
		manager.signForm(tax);
		std::cout << tax << std::endl;
	}
	catch (const std::exception &error)
	{
		std::cout << "Caught exception: " << error.what() << std::endl;
	}
	return (0);
}
