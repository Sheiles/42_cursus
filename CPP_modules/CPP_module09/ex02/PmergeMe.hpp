#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <vector>

class PmergeMe
{
public:
	PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();

	void sortVector(std::vector<unsigned int> &values) const;
	void sortDeque(std::deque<unsigned int> &values) const;
};

#endif
