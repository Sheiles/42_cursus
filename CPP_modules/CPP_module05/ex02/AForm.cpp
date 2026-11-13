#include "AForm.hpp"

#include "Bureaucrat.hpp"

#include <ostream>

AForm::AForm(const std::string &name, int grade_to_sign, int grade_to_execute)
	: _name(name), _is_signed(false), _grade_to_sign(grade_to_sign),
	 _grade_to_execute(grade_to_execute)
{
	validate_grade(grade_to_sign);
	validate_grade(grade_to_execute);
}

AForm::AForm(const AForm &other)
	: _name(other._name), _is_signed(other._is_signed),
	 _grade_to_sign(other._grade_to_sign),
	 _grade_to_execute(other._grade_to_execute)
{
}

AForm::~AForm()
{
}

AForm &AForm::operator=(const AForm &other)
{
	if (this != &other)
	{
		_is_signed = other._is_signed;
	}
	return (*this);
}

const std::string &AForm::getName() const
{
	return (_name);
}

bool AForm::getIsSigned() const
{
	return (_is_signed);
}

int AForm::getGradeToSign() const
{
	return (_grade_to_sign);
}

int AForm::getGradeToExecute() const
{
	return (_grade_to_execute);
}

void AForm::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() > _grade_to_sign)
	{
		throw GradeTooLowException();
	}
	_is_signed = true;
}

void AForm::execute(const Bureaucrat &executor) const
{
	if (!_is_signed)
	{
		throw NotSignedException();
	}
	if (executor.getGrade() > _grade_to_execute)
	{
		throw GradeTooLowException();
	}
	execute_action();
}

void AForm::validate_grade(int grade) const
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

const char *AForm::GradeTooHighException::what() const throw()
{
	return ("Form grade is too high");
}

const char *AForm::GradeTooLowException::what() const throw()
{
	return ("Form grade is too low");
}

const char *AForm::NotSignedException::what() const throw()
{
	return ("form is not signed");
}

std::ostream &operator<<(std::ostream &out, const AForm &form)
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
