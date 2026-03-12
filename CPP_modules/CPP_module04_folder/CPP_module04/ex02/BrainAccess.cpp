#include "Brain.hpp"

void Brain::setIdea(int idx, const std::string &idea)
{
	if (idx >= 0 && idx < 100)
		this->ideas[idx] = idea;
}

std::string Brain::getIdea(int idx) const
{
	if (idx >= 0 && idx < 100)
		return this->ideas[idx];
	return "";
}