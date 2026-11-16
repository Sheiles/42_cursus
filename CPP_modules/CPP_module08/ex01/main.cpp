#include "Span.hpp"

#include <iostream>
#include <limits>
#include <vector>

int main()
{
	try
	{
		Span example(5);
		example.addNumber(6);
		example.addNumber(3);
		example.addNumber(17);
		example.addNumber(9);
		example.addNumber(11);
		std::cout << "shortest: " << example.shortestSpan() << std::endl;
		std::cout << "longest: " << example.longestSpan() << std::endl;

		Span empty(0);
		try
		{
			empty.shortestSpan();
		}
		catch (const std::exception &error)
		{
			std::cout << "empty shortest: " << error.what() << std::endl;
		}
		try
		{
			empty.longestSpan();
		}
		catch (const std::exception &error)
		{
			std::cout << "empty longest: " << error.what() << std::endl;
		}

		Span single(1);
		single.addNumber(42);
		try
		{
			single.shortestSpan();
		}
		catch (const std::exception &error)
		{
			std::cout << "single shortest: " << error.what() << std::endl;
		}
		try
		{
			single.longestSpan();
		}
		catch (const std::exception &error)
		{
			std::cout << "single longest: " << error.what() << std::endl;
		}

		Span duplicates(4);
		duplicates.addNumber(5);
		duplicates.addNumber(5);
		duplicates.addNumber(8);
		duplicates.addNumber(8);
		std::cout << "duplicate shortest: " << duplicates.shortestSpan() << std::endl;
		std::cout << "duplicate longest: " << duplicates.longestSpan() << std::endl;

		Span original(3);
		original.addNumber(1);
		original.addNumber(4);
		Span copied(original);
		original.addNumber(10);
		std::cout << "copied shortest: " << copied.shortestSpan() << std::endl;
		std::cout << "copied longest after original changes: "
			<< copied.longestSpan() << std::endl;

		Span large(10000);
		std::vector<int> numbers;
		for (int i = 0; i < 10000; ++i)
			numbers.push_back(i * 3);
		large.addNumbers(numbers.begin(), numbers.end());
		std::cout << "large shortest: " << large.shortestSpan() << std::endl;
		std::cout << "large longest: " << large.longestSpan() << std::endl;

		Span extremes(2);
		extremes.addNumber(std::numeric_limits<int>::min());
		extremes.addNumber(std::numeric_limits<int>::max());
		std::cout << "extreme span: " << extremes.longestSpan() << std::endl;

		try
		{
			example.addNumber(13);
		}
		catch (const std::exception &error)
		{
			std::cout << "capacity: " << error.what() << std::endl;
		}

		try
		{
			Span tooSmall(2);
			tooSmall.addNumbers(numbers.begin(), numbers.end());
		}
		catch (const std::exception &error)
		{
			std::cout << "range capacity: " << error.what() << std::endl;
		}
	}
	catch (const std::exception &error)
	{
		std::cerr << "error: " << error.what() << std::endl;
		return 1;
	}
	return 0;
}
