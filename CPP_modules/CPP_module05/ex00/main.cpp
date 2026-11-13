#include "Bureaucrat.hpp"

#include <iostream>
#include <sstream>
#include <string>

static bool report_exception_mismatch(const std::string &test,
	const std::string &expected, const std::string &actual,
	const std::string &message)
{
	std::cerr << test << ": expected " << expected << ", caught " << actual
		<< " (" << message << ")." << std::endl;
	return (false);
}

static bool report_missing_exception(const std::string &test,
	const std::string &expected)
{
	std::cerr << test << ": expected " << expected
		<< ", but no exception was thrown." << std::endl;
	return (false);
}

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
	catch (const Bureaucrat::GradeTooLowException &error)
	{
		return (report_exception_mismatch("Grade 0 construction",
				"GradeTooHighException", "GradeTooLowException", error.what()));
	}
	catch (const std::exception &error)
	{
		return (report_exception_mismatch("Grade 0 construction",
				"GradeTooHighException", "std::exception", error.what()));
	}
	if (!high_grade_rejected)
	{
		return (report_missing_exception("Grade 0 construction",
				"GradeTooHighException"));
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
	catch (const Bureaucrat::GradeTooHighException &error)
	{
		return (report_exception_mismatch("Grade 151 construction",
				"GradeTooLowException", "GradeTooHighException", error.what()));
	}
	catch (const std::exception &error)
	{
		return (report_exception_mismatch("Grade 151 construction",
				"GradeTooLowException", "std::exception", error.what()));
	}
	if (!low_grade_rejected)
	{
		return (report_missing_exception("Grade 151 construction",
				"GradeTooLowException"));
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
		return (report_missing_exception("Incrementing grade 1",
				"GradeTooHighException"));
	}
	catch (const Bureaucrat::GradeTooHighException &)
	{
	}
	catch (const Bureaucrat::GradeTooLowException &error)
	{
		return (report_exception_mismatch("Incrementing grade 1",
				"GradeTooHighException", "GradeTooLowException", error.what()));
	}
	catch (const std::exception &error)
	{
		return (report_exception_mismatch("Incrementing grade 1",
				"GradeTooHighException", "std::exception", error.what()));
	}
	try
	{
		lowest.decrementGrade();
		return (report_missing_exception("Decrementing grade 150",
				"GradeTooLowException"));
	}
	catch (const Bureaucrat::GradeTooLowException &)
	{
	}
	catch (const Bureaucrat::GradeTooHighException &error)
	{
		return (report_exception_mismatch("Decrementing grade 150",
				"GradeTooLowException", "GradeTooHighException", error.what()));
	}
	catch (const std::exception &error)
	{
		return (report_exception_mismatch("Decrementing grade 150",
				"GradeTooLowException", "std::exception", error.what()));
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

static bool test_stream_output()
{
	Bureaucrat employee("Alice", 42);
	std::ostringstream output;

	output << employee;
	return (output.str() == "Alice, bureaucrat grade 42.");
}

static bool report_test(const std::string &name, bool (*test)())
{
	bool passed;

	try
	{
		passed = test();
	}
	catch (const Bureaucrat::GradeTooHighException &error)
	{
		report_exception_mismatch(name, "no exception",
			"GradeTooHighException", error.what());
		passed = false;
	}
	catch (const Bureaucrat::GradeTooLowException &error)
	{
		report_exception_mismatch(name, "no exception",
			"GradeTooLowException", error.what());
		passed = false;
	}
	catch (const std::exception &error)
	{
		report_exception_mismatch(name, "no exception", "std::exception",
			error.what());
		passed = false;
	}
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
	if (!report_test("Valid boundary grades", test_valid_boundary_grades))
		all_passed = false;
	if (!report_test("Invalid boundary grades", test_invalid_boundary_grades))
		all_passed = false;
	if (!report_test("Successful grade changes", test_successful_grade_changes))
		all_passed = false;
	if (!report_test("Exception preserves grade",
			test_grade_exceptions_preserve_state))
		all_passed = false;
	if (!report_test("Copy and assignment", test_copy_and_assignment))
		all_passed = false;
	if (!report_test("Stream output", test_stream_output))
		all_passed = false;
	if (all_passed)
		return (0);
	return (1);
}
