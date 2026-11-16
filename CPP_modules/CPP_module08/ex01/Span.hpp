#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>

class Span
{
public:
	explicit Span(unsigned int capacity);
	Span(const Span &other);
	Span &operator=(const Span &other);
	~Span();

	void addNumber(int number);

	template <typename InputIterator>
	void addNumbers(InputIterator first, InputIterator last)
	{
		std::vector<int> additions(first, last);
		if (additions.size() > _capacity - _numbers.size())
			throwSpanFull();
		_numbers.insert(_numbers.end(), additions.begin(), additions.end());
	}

	unsigned int shortestSpan() const;
	unsigned int longestSpan() const;

private:
	unsigned int _capacity;
	std::vector<int> _numbers;

	void throwSpanFull() const;
	void ensureSpanExists() const;
};

#endif
