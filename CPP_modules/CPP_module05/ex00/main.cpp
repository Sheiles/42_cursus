#include "Bureaucrat.hpp"

#include <iostream>
#include <string>

static bool test_valid_boundary_grades()
{
	Bureaucrat highest("Highest", 1);
	Bureaucrat lowest("Lowest", 150);

	return (highest.getGrade() == 1 && lowest.getGrade() == 150);
}

static bool test_invalid_boundary_grades()
{
	bool high_grade_rejected;
	bool low_grade_rejected;

	high_grade_rejected = false;
	low_grade_rejected = false;
	try
	{
		Bureaucrat invalid("Too high", 0);

		(void)invalid;
	}
	catch (const Bureaucrat::GradeTooHighException &)
	{
		high_grade_rejected = true;
	}
	catch (const std::exception &)
	{
		return (false);
	}
	try
	{
		Bureaucrat invalid("Too low", 151);

		(void)invalid;
	}
	catch (const Bureaucrat::GradeTooLowException &)
	{
		low_grade_rejected = true;
	}
	catch (const std::exception &)
	{
		return (false);
	}
	return (high_grade_rejected && low_grade_rejected);
}

static bool test_successful_grade_changes()
{
	Bureaucrat employee("Employee", 3);

	employee.incrementGrade();
	if (employee.getGrade() != 2)
		return (false);
	employee.decrementGrade();
	return (employee.getGrade() == 3);
}

static bool test_grade_exceptions_preserve_state()
{
	Bureaucrat highest("Highest", 1);
	Bureaucrat lowest("Lowest", 150);

	try
	{
		highest.incrementGrade();
		return (false);
	}
	catch (const Bureaucrat::GradeTooHighException &)
	{
	}
	catch (const std::exception &)
	{
		return (false);
	}
	try
	{
		lowest.decrementGrade();
		return (false);
	}
	catch (const Bureaucrat::GradeTooLowException &)
	{
	}
	catch (const std::exception &)
	{
		return (false);
	}
	return (highest.getGrade() == 1 && lowest.getGrade() == 150);
}

static bool test_copy_and_assignment()
{
	Bureaucrat source("Source", 42);
	Bureaucrat copied(source);
	Bureaucrat assigned("Assigned", 99);

	assigned = source;
	return (copied.getName() == "Source" && copied.getGrade() == 42
		&& assigned.getName() == "Assigned" && assigned.getGrade() == 42);
}

static bool report_test(const std::string &name, bool passed)
{
	std::cout << name << ": ";
	if (passed)
		std::cout << "PASS" << std::endl;
	else
		std::cout << "FAIL" << std::endl;
	return (passed);
}

int main()
{
	bool all_passed;

	all_passed = true;
	if (!report_test("Valid boundary grades", test_valid_boundary_grades()))
		all_passed = false;
	if (!report_test("Invalid boundary grades", test_invalid_boundary_grades()))
		all_passed = false;
	if (!report_test("Successful grade changes", test_successful_grade_changes()))
		all_passed = false;
	if (!report_test("Exception preserves grade",
			test_grade_exceptions_preserve_state()))
		all_passed = false;
	if (!report_test("Copy and assignment", test_copy_and_assignment()))
		all_passed = false;
	if (all_passed)
		return (0);
	return (1);
}
