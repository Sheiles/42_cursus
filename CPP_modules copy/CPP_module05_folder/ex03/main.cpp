/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 14:13:53 by sheiles           #+#    #+#             */
/*   Updated: 2026/11/19 14:13:55 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"

#include <iostream>
#include <string>

static int run_known_form(Intern &intern, const std::string &form_name,
	const std::string &target)
{
	AForm *form;

	form = intern.makeForm(form_name, target);
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
	AForm *unknown_form;

	if (run_known_form(intern, "shrubbery creation", "intern_test") != 0)
	{
		return (1);
	}
	if (run_known_form(intern, "robotomy request", "Bender") != 0)
	{
		return (1);
	}
	if (run_known_form(intern, "presidential pardon", "Arthur Dent") != 0)
	{
		return (1);
	}
	unknown_form = intern.makeForm("unknown form", "target");
	if (unknown_form != NULL)
	{
		delete unknown_form;
		return (1);
	}
	return (0);
}
