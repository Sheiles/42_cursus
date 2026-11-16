#include "RPN.hpp"

#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

RPN::RPN()
{
}

RPN::RPN(const RPN &)
{
}

RPN &RPN::operator=(const RPN &)
{
	return *this;
}

RPN::~RPN()
{
}

double RPN::evaluate(const std::string &expression) const
{
	std::istringstream input(expression);
	std::stack<double> values;
	std::string token;
	bool sawToken = false;

	while (input >> token)
	{
		sawToken = true;
		if (token.size() == 1 && token[0] >= '0' && token[0] <= '9')
		{
			values.push(static_cast<double>(token[0] - '0'));
			continue;
		}
		if (token.size() != 1
			|| (token[0] != '+' && token[0] != '-' && token[0] != '*'
				&& token[0] != '/'))
			throw std::runtime_error("invalid token");
		if (values.size() < 2)
			throw std::runtime_error("invalid expression");

		double right = values.top();
		values.pop();
		double left = values.top();
		values.pop();
		switch (token[0])
		{
			case '+':
				values.push(left + right);
				break;
			case '-':
				values.push(left - right);
				break;
			case '*':
				values.push(left * right);
				break;
			case '/':
				if (right == 0.0)
					throw std::runtime_error("division by zero");
				values.push(left / right);
				break;
		}
	}
	if (!sawToken || values.size() != 1)
		throw std::runtime_error("invalid expression");
	return values.top();
}
