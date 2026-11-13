#include "ShrubberyCreationForm.hpp"

#include <fstream>
#include <stdexcept>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
	: AForm("ShrubberyCreationForm", 145, 137), _target(target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(
	const ShrubberyCreationForm &other)
	: AForm(other), _target(other._target)
{
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(
	const ShrubberyCreationForm &other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return (*this);
}

const std::string &ShrubberyCreationForm::get_target() const
{
	return (_target);
}

void ShrubberyCreationForm::execute_action() const
{
	std::ofstream output((_target + "_shrubbery").c_str());
	if (!output)
	{
		throw std::runtime_error("could not create shrubbery file");
	}
	output << "       *\n"
		<< "      /*\\\n"
		<< "     /***\\\n"
		<< "    /*****\\\n"
		<< "       ||\n"
		<< "       ||\n";
	output.close();
	if (!output)
	{
		throw std::runtime_error("could not write shrubbery file");
	}
}
