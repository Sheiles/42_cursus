/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 14:12:10 by sheiles           #+#    #+#             */
/*   Updated: 2026/11/19 14:12:12 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

static bool test_execution_authorization()
{
	ShrubberyCreationForm form("garden");
	Bureaucrat exact_signer("Exact signer", 145);
	Bureaucrat insufficient_executor("Insufficient executor", 138);
	Bureaucrat exact_executor("Exact executor", 137);

	try
	{
		form.execute(exact_executor);
		return (false);
	}
	catch (const AForm::NotSignedException &)
	{
	}
	catch (const std::exception &)
	{
		return (false);
	}
	try
	{
		form.beSigned(exact_signer);
	}
	catch (const std::exception &)
	{
		return (false);
	}
	if (!form.getIsSigned())
		return (false);
	try
	{
		form.execute(insufficient_executor);
		return (false);
	}
	catch (const AForm::GradeTooLowException &)
	{
	}
	catch (const std::exception &)
	{
		return (false);
	}
	try
	{
		form.execute(exact_executor);
	}
	catch (const std::exception &)
	{
		return (false);
	}
	return (true);
}

static bool test_exact_thresholds(AForm &form, int sign_grade,
	int execute_grade)
{
	Bureaucrat signer("Exact signer", sign_grade);
	Bureaucrat executor("Exact executor", execute_grade);

	if (form.getGradeToSign() != sign_grade
		|| form.getGradeToExecute() != execute_grade)
	{
		return (false);
	}
	try
	{
		form.beSigned(signer);
	}
	catch (const std::exception &)
	{
		return (false);
	}
	if (!form.getIsSigned())
		return (false);
	try
	{
		form.execute(executor);
	}
	catch (const std::exception &)
	{
		return (false);
	}
	return (true);
}

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
	std::srand(static_cast<unsigned int>(std::time(0)));
	try
	{
		Bureaucrat executive("Executive", 1);
		Bureaucrat senior("Senior", 60);
		ShrubberyCreationForm shrubbery("garden");
		RobotomyRequestForm robotomy("Bender");
		PresidentialPardonForm pardon("Arthur Dent");

		if (!test_execution_authorization())
		{
			std::cerr << "Form execution authorization test failed."
				<< std::endl;
			return (1);
		}
		if (!test_exact_thresholds(robotomy, 72, 45))
		{
			std::cerr << "Robotomy form threshold test failed."
				<< std::endl;
			return (1);
		}
		if (!test_exact_thresholds(pardon, 25, 5))
		{
			std::cerr << "Presidential pardon threshold test failed."
				<< std::endl;
			return (1);
		}
		test_shrubbery(executive, shrubbery);
		test_robotomy(executive, senior, robotomy);
		test_pardon(executive, pardon);
	}
	catch (const std::exception &error)
	{
		std::cerr << "Caught exception: " << error.what() << std::endl;
		return (1);
	}
	return (0);
}
