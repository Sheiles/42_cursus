#include "Span.hpp"

#include <algorithm>
#include <stdexcept>

Span::Span(unsigned int capacity) : _capacity(capacity)
{
	_numbers.reserve(capacity);
}

Span::Span(const Span &other)
	: _capacity(other._capacity), _numbers(other._numbers)
{
}

Span &Span::operator=(const Span &other)
{
	if (this != &other)
	{
		_capacity = other._capacity;
		_numbers = other._numbers;
	}
	return *this;
}

Span::~Span()
{
}

void Span::addNumber(int number)
{
	if (_numbers.size() >= _capacity)
		throwSpanFull();
	_numbers.push_back(number);
}

void Span::throwSpanFull() const
{
	throw std::length_error("Span is full");
}

void Span::ensureSpanExists() const
{
	if (_numbers.size() < 2)
		throw std::logic_error("Cannot calculate a span with fewer than two numbers");
}

unsigned int Span::shortestSpan() const
{
	ensureSpanExists();
	std::vector<int> sorted(_numbers);
	std::sort(sorted.begin(), sorted.end());

	unsigned int shortest = static_cast<unsigned int>(sorted[1])
		- static_cast<unsigned int>(sorted[0]);
	for (std::vector<int>::size_type i = 2; i < sorted.size(); ++i)
	{
		unsigned int difference = static_cast<unsigned int>(sorted[i])
			- static_cast<unsigned int>(sorted[i - 1]);
		if (difference < shortest)
			shortest = difference;
	}
	return shortest;
}

unsigned int Span::longestSpan() const
{
	ensureSpanExists();
	std::vector<int>::const_iterator minimum =
		std::min_element(_numbers.begin(), _numbers.end());
	std::vector<int>::const_iterator maximum =
		std::max_element(_numbers.begin(), _numbers.end());
	return static_cast<unsigned int>(*maximum)
		- static_cast<unsigned int>(*minimum);
}
