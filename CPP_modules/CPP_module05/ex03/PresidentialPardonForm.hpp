#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

#include <string>

class PresidentialPardonForm : public AForm
{
public:
	explicit PresidentialPardonForm(const std::string &target);
	PresidentialPardonForm(const PresidentialPardonForm &other);
	virtual ~PresidentialPardonForm();
	PresidentialPardonForm &operator=(const PresidentialPardonForm &other);

	const std::string &get_target() const;

protected:
	virtual void execute_action() const;

private:
	std::string _target;
};

#endif
