/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 14:11:55 by sheiles           #+#    #+#             */
/*   Updated: 2026/11/19 14:11:59 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
#define AFORM_HPP

#include <exception>
#include <iosfwd>
#include <string>

class Bureaucrat;

class AForm
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

	class NotSignedException : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

	AForm(const std::string &name, int grade_to_sign, int grade_to_execute);
	AForm(const AForm &other);
	virtual ~AForm();
	AForm &operator=(const AForm &other);

	const std::string &getName() const;
	bool getIsSigned() const;
	int getGradeToSign() const;
	int getGradeToExecute() const;
	void beSigned(const Bureaucrat &bureaucrat);
	void execute(const Bureaucrat &executor) const;

private:
	const std::string _name;
	bool _is_signed;
	const int _grade_to_sign;
	const int _grade_to_execute;

protected:
	virtual void execute_action() const = 0;

private:
	void validate_grade(int grade) const;
};

std::ostream &operator<<(std::ostream &out, const AForm &form);

#endif
