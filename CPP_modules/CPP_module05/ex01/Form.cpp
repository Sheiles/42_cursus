#include "Form.hpp"

#include "Bureaucrat.hpp"

#include <ostream>

Form::Form(const std::string &name, int grade_to_sign, int grade_to_execute)
	: _name(name), _is_signed(false), _grade_to_sign(grade_to_sign),
	 _grade_to_execute(grade_to_execute)
{
	validate_grade(grade_to_sign);
	validate_grade(grade_to_execute);
}

Form::Form(const Form &other)
	: _name(other._name), _is_signed(other._is_signed),
	 _grade_to_sign(other._grade_to_sign),
	 _grade_to_execute(other._grade_to_execute)
{
}

Form::~Form()
{
}

Form &Form::operator=(const Form &other)
{
	if (this != &other)
	{
		_is_signed = other._is_signed;
	}
	return (*this);
}

const std::string &Form::getName() const
{
	return (_name);
}

bool Form::getIsSigned() const
{
	return (_is_signed);
}

int Form::getGradeToSign() const
{
	return (_grade_to_sign);
}

int Form::getGradeToExecute() const
{
	return (_grade_to_execute);
}

void Form::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() > _grade_to_sign)
	{
		throw GradeTooLowException();
	}
	_is_signed = true;
}

void Form::validate_grade(int grade) const
{
	if (grade < 1)
	{
		throw GradeTooHighException();
	}
	if (grade > 150)
	{
		throw GradeTooLowException();
	}
}

const char *Form::GradeTooHighException::what() const throw()
{
	return ("Form grade is too high");
}

const char *Form::GradeTooLowException::what() const throw()
{
	return ("Form grade is too low");
}

std::ostream &operator<<(std::ostream &out, const Form &form)
{
	out << "Form " << form.getName() << ", signed: ";
	if (form.getIsSigned())
	{
		out << "yes";
	}
	else
	{
		out << "no";
	}
	out << ", grade required to sign: " << form.getGradeToSign()
		<< ", grade required to execute: " << form.getGradeToExecute() << ".";
	return (out);
}
