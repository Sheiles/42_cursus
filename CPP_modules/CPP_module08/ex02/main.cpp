#include "MutantStack.hpp"

#include <iostream>
#include <list>
#include <stack>

int main()
{
	MutantStack<int> values;
	values.push(5);
	values.push(17);
	std::cout << "top: " << values.top() << std::endl;
	values.pop();
	values.push(3);
	values.push(5);
	values.push(737);
	values.push(0);

	*values.begin() = 42;
	std::cout << "modified first: " << *values.begin() << std::endl;

	std::cout << "forward:";
	for (MutantStack<int>::iterator it = values.begin(); it != values.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;

	std::cout << "reverse:";
	for (MutantStack<int>::reverse_iterator rit = values.rbegin();
		rit != values.rend(); ++rit)
		std::cout << " " << *rit;
	std::cout << std::endl;

	const MutantStack<int> constValues(values);
	std::cout << "const iteration:";
	for (MutantStack<int>::const_iterator it = constValues.begin();
		it != constValues.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;

	std::stack<int> ordinaryStack(values);
	std::list<int> list(values.begin(), values.end());
	std::cout << "same size: "
		<< (ordinaryStack.size() == list.size()) << std::endl;
	return 0;
}
