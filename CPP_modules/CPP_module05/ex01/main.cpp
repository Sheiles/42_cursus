#include "Bureaucrat.hpp"
#include "Form.hpp"

#include <iostream>

enum ExpectedGradeResult
{
	EXPECTED_GRADE_VALID,
	EXPECTED_GRADE_TOO_HIGH,
	EXPECTED_GRADE_TOO_LOW
};

static bool check_form_grade(int grade, bool is_sign_grade,
	ExpectedGradeResult expected)
{
	try
	{
		if (is_sign_grade)
		{
			Form form("Grade test", grade, 50);
			(void)form;
		}
		else
		{
			Form form("Grade test", 50, grade);
			(void)form;
		}
		return (expected == EXPECTED_GRADE_VALID);
	}
	catch (const Form::GradeTooHighException &)
	{
		return (expected == EXPECTED_GRADE_TOO_HIGH);
	}
	catch (const Form::GradeTooLowException &)
	{
		return (expected == EXPECTED_GRADE_TOO_LOW);
	}
}

static bool check_form_grade_boundaries()
{
	const int grades[] = {0, 1, 150, 151};
	const ExpectedGradeResult expected[] = {
		EXPECTED_GRADE_TOO_HIGH,
		EXPECTED_GRADE_VALID,
		EXPECTED_GRADE_VALID,
		EXPECTED_GRADE_TOO_LOW
	};
	unsigned int i;

	for (i = 0; i < sizeof(grades) / sizeof(grades[0]); ++i)
	{
		if (!check_form_grade(grades[i], true, expected[i])
			|| !check_form_grade(grades[i], false, expected[i]))
		{
			return (false);
		}
	}
	return (true);
}

static bool check_form_copy_and_assignment()
{
	Form original("Original", 50, 25);
	Bureaucrat signer("Signer", 50);

	original.beSigned(signer);
	Form copied(original);
	if (copied.getName() != "Original" || !copied.getIsSigned()
		|| copied.getGradeToSign() != 50 || copied.getGradeToExecute() != 25)
	{
		return (false);
	}

	Form assigned("Destination", 100, 75);
	assigned = original;
	return (assigned.getName() == "Destination"
		&& assigned.getIsSigned()
		&& assigned.getGradeToSign() == 100
		&& assigned.getGradeToExecute() == 75);
}

static bool check_bureaucrat_grade(int grade, ExpectedGradeResult expected)
{
	try
	{
		Bureaucrat bureaucrat("Grade test", grade);
		(void)bureaucrat;
		return (expected == EXPECTED_GRADE_VALID);
	}
	catch (const Bureaucrat::GradeTooHighException &)
	{
		return (expected == EXPECTED_GRADE_TOO_HIGH);
	}
	catch (const Bureaucrat::GradeTooLowException &)
	{
		return (expected == EXPECTED_GRADE_TOO_LOW);
	}
}

static bool check_bureaucrat_grade_boundaries()
{
	return (check_bureaucrat_grade(0, EXPECTED_GRADE_TOO_HIGH)
		&& check_bureaucrat_grade(1, EXPECTED_GRADE_VALID)
		&& check_bureaucrat_grade(150, EXPECTED_GRADE_VALID)
		&& check_bureaucrat_grade(151, EXPECTED_GRADE_TOO_LOW));
}

static bool check_bureaucrat_grade_adjustments()
{
	Bureaucrat top("Top", 1);
	try
	{
		top.incrementGrade();
		return (false);
	}
	catch (const Bureaucrat::GradeTooHighException &)
	{
	}
	if (top.getGrade() != 1)
	{
		return (false);
	}
	top.decrementGrade();
	if (top.getGrade() != 2)
	{
		return (false);
	}

	Bureaucrat bottom("Bottom", 150);
	try
	{
		bottom.decrementGrade();
		return (false);
	}
	catch (const Bureaucrat::GradeTooLowException &)
	{
	}
	if (bottom.getGrade() != 150)
	{
		return (false);
	}
	bottom.incrementGrade();
	return (bottom.getGrade() == 149);
}

static bool check_equal_grade_and_resigning()
{
	Form form("Exact grade form", 50, 25);
	Bureaucrat signer("Exact grade signer", 50);

	form.beSigned(signer);
	if (!form.getIsSigned())
	{
		return (false);
	}
	form.beSigned(signer);
	return (form.getIsSigned());
}

int main()
{
	if (!check_form_grade_boundaries())
	{
		std::cerr << "Form grade boundary test failed." << std::endl;
		return (1);
	}
	if (!check_form_copy_and_assignment())
	{
		std::cerr << "Form copy/assignment test failed." << std::endl;
		return (1);
	}
	if (!check_bureaucrat_grade_boundaries())
	{
		std::cerr << "Bureaucrat grade boundary test failed." << std::endl;
		return (1);
	}
	if (!check_bureaucrat_grade_adjustments())
	{
		std::cerr << "Bureaucrat grade adjustment test failed." << std::endl;
		return (1);
	}
	if (!check_equal_grade_and_resigning())
	{
		std::cerr << "Form signing test failed." << std::endl;
		return (1);
	}

	try
	{
		Form tax("Tax form", 50, 25);
		Bureaucrat intern("Intern", 100);
		Bureaucrat manager("Manager", 20);

		std::cout << tax << std::endl;
		intern.signForm(tax);
		if (tax.getIsSigned())
		{
			std::cerr << "A refused signature unexpectedly signed the form."
				<< std::endl;
			return (1);
		}
		manager.signForm(tax);
		if (!tax.getIsSigned())
		{
			std::cerr << "An accepted signature did not sign the form."
				<< std::endl;
			return (1);
		}
		std::cout << tax << std::endl;
	}
	catch (const std::exception &error)
	{
		std::cerr << "Caught exception: " << error.what() << std::endl;
		return (1);
	}
	return (0);
}
