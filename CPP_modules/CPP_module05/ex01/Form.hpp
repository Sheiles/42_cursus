#ifndef FORM_HPP
#define FORM_HPP

#include <exception>
#include <iosfwd>
#include <string>

class Bureaucrat;

class Form
{
public:
	class GradeTooHighException : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

	Form(const std::string &name, int grade_to_sign, int grade_to_execute);
	Form(const Form &other);
	~Form();
	Form &operator=(const Form &other);

	const std::string &getName() const;
	bool getIsSigned() const;
	int getGradeToSign() const;
	int getGradeToExecute() const;
	void beSigned(const Bureaucrat &bureaucrat);

private:
	const std::string _name;
	bool _is_signed;
	const int _grade_to_sign;
	const int _grade_to_execute;

	void validate_grade(int grade) const;
};

std::ostream &operator<<(std::ostream &out, const Form &form);

#endif
