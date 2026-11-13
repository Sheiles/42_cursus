#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"

#include <string>

class RobotomyRequestForm : public AForm
{
public:
	explicit RobotomyRequestForm(const std::string &target);
	RobotomyRequestForm(const RobotomyRequestForm &other);
	virtual ~RobotomyRequestForm();
	RobotomyRequestForm &operator=(const RobotomyRequestForm &other);

	const std::string &get_target() const;

protected:
	virtual void execute_action() const;

private:
	std::string _target;
};

#endif
