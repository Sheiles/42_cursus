#include "ScalarConverter.hpp"

#include <cerrno>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

namespace
{
	enum LiteralType
	{
		CHAR_LITERAL,
		INT_LITERAL,
		FLOAT_LITERAL,
		DOUBLE_LITERAL,
		SPECIAL_LITERAL,
		INVALID_LITERAL
	};

	bool isInteger(const std::string &text)
	{
		std::string::size_type index;

		if (text.empty())
			return (false);
		index = 0;
		if (text[index] == '+' || text[index] == '-')
			++index;
		if (index == text.size())
			return (false);
		for (; index < text.size(); ++index)
		{
			if (!std::isdigit(static_cast<unsigned char>(text[index])))
				return (false);
		}
		return (true);
	}

	bool isDecimal(const std::string &text)
	{
		std::string::size_type index;
		bool has_digit;

		if (text.empty())
			return (false);
		index = 0;
		if (text[index] == '+' || text[index] == '-')
			++index;
		has_digit = false;
		while (index < text.size()
			&& std::isdigit(static_cast<unsigned char>(text[index])))
		{
			has_digit = true;
			++index;
		}
		if (index < text.size() && text[index] == '.')
		{
			++index;
			while (index < text.size()
				&& std::isdigit(static_cast<unsigned char>(text[index])))
			{
				has_digit = true;
				++index;
			}
		}
		if (!has_digit)
			return (false);
		if (index < text.size() && (text[index] == 'e' || text[index] == 'E'))
		{
			++index;
			if (index < text.size() && (text[index] == '+' || text[index] == '-'))
				++index;
			if (index == text.size()
				|| !std::isdigit(static_cast<unsigned char>(text[index])))
				return (false);
			while (index < text.size()
				&& std::isdigit(static_cast<unsigned char>(text[index])))
				++index;
		}
		return (index == text.size());
	}

	LiteralType detectType(const std::string &text)
	{
		if (text.size() == 1
			&& std::isprint(static_cast<unsigned char>(text[0]))
			&& !std::isdigit(static_cast<unsigned char>(text[0])))
			return (CHAR_LITERAL);
		if (text.size() == 3 && text[0] == '\'' && text[2] == '\''
			&& std::isprint(static_cast<unsigned char>(text[1])))
			return (CHAR_LITERAL);
		if (text == "nan" || text == "+inf" || text == "-inf"
			|| text == "nanf" || text == "+inff" || text == "-inff")
			return (SPECIAL_LITERAL);
		if (isInteger(text))
			return (INT_LITERAL);
		if (text.size() > 1 && text[text.size() - 1] == 'f'
			&& isDecimal(text.substr(0, text.size() - 1)))
			return (FLOAT_LITERAL);
		if (isDecimal(text))
			return (DOUBLE_LITERAL);
		return (INVALID_LITERAL);
	}

	double parseSpecial(const std::string &text)
	{
		if (text == "nan" || text == "nanf")
			return (std::numeric_limits<double>::quiet_NaN());
		if (text == "-inf" || text == "-inff")
			return (-std::numeric_limits<double>::infinity());
		return (std::numeric_limits<double>::infinity());
	}

	bool isFinite(double value)
	{
		return (value == value
			&& value <= std::numeric_limits<double>::max()
			&& value >= -std::numeric_limits<double>::max());
	}

	std::string formatNumber(double value, int precision)
	{
		std::ostringstream output;
		std::string text;

		output << std::setprecision(precision) << value;
		text = output.str();
		if (text.find('.') == std::string::npos
			&& text.find('e') == std::string::npos
			&& text.find('E') == std::string::npos)
			text += ".0";
		return (text);
	}

	int maxDigits10(int digits, int radix)
	{
		double precision;

		precision = 1.0 + static_cast<double>(digits)
			* std::log10(static_cast<double>(radix));
		return (static_cast<int>(std::ceil(precision)));
	}

	void printChar(double value, bool sourceIsChar, char sourceChar)
	{
		char converted;

		std::cout << "char: ";
		if (sourceIsChar)
			converted = sourceChar;
		else
		{
			if (!isFinite(value) || value < std::numeric_limits<char>::min()
				|| value > std::numeric_limits<char>::max())
			{
				std::cout << "impossible" << std::endl;
				return ;
			}
			converted = static_cast<char>(value);
		}
		if (!std::isprint(static_cast<unsigned char>(converted)))
			std::cout << "Non displayable" << std::endl;
		else
			std::cout << '\'' << converted << '\'' << std::endl;
	}

	void printInt(double value)
	{
		std::cout << "int: ";
		if (!isFinite(value)
			|| value < static_cast<double>(std::numeric_limits<int>::min())
			|| value > static_cast<double>(std::numeric_limits<int>::max()))
			std::cout << "impossible" << std::endl;
		else
			std::cout << static_cast<int>(value) << std::endl;
	}

	void printFloat(double value)
	{
		std::cout << "float: ";
		if (value != value)
			std::cout << "nanf" << std::endl;
		else if (value > std::numeric_limits<double>::max())
			std::cout << "+inff" << std::endl;
		else if (value < -std::numeric_limits<double>::max())
			std::cout << "-inff" << std::endl;
		else if (value > std::numeric_limits<float>::max()
			|| value < -std::numeric_limits<float>::max())
			std::cout << "impossible" << std::endl;
		else
			std::cout << formatNumber(static_cast<float>(value),
					maxDigits10(std::numeric_limits<float>::digits,
						std::numeric_limits<float>::radix)) << 'f'
				<< std::endl;
	}

	void printDouble(double value)
	{
		std::cout << "double: ";
		if (value != value)
			std::cout << "nan" << std::endl;
		else if (value > std::numeric_limits<double>::max())
			std::cout << "+inf" << std::endl;
		else if (value < -std::numeric_limits<double>::max())
			std::cout << "-inf" << std::endl;
		else
			std::cout << formatNumber(value,
					maxDigits10(std::numeric_limits<double>::digits,
						std::numeric_limits<double>::radix)) << std::endl;
	}
}

void ScalarConverter::convert(const std::string &literal)
{
	LiteralType type;
	double value;
	char character;

	type = detectType(literal);
	if (type == INVALID_LITERAL)
	{
		std::cout << "Error: invalid literal" << std::endl;
		return ;
	}
	character = '\0';
	if (type == CHAR_LITERAL)
	{
		character = (literal.size() == 1) ? literal[0] : literal[1];
		value = static_cast<double>(character);
	}
	else if (type == SPECIAL_LITERAL)
		value = parseSpecial(literal);
	else
	{
		std::string numericText(literal);

		if (type == FLOAT_LITERAL)
			numericText.erase(numericText.size() - 1);
		errno = 0;
		value = std::strtod(numericText.c_str(), 0);
		if (errno == ERANGE && !isFinite(value))
		{
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: impossible" << std::endl;
			std::cout << "double: impossible" << std::endl;
			return ;
		}
		if (type == FLOAT_LITERAL)
		{
			float floatValue;

			floatValue = ::strtof(numericText.c_str(), 0);
			if (floatValue == floatValue
				&& floatValue <= std::numeric_limits<float>::max()
				&& floatValue >= -std::numeric_limits<float>::max())
				value = static_cast<double>(floatValue);
		}
	}
	printChar(value, type == CHAR_LITERAL, character);
	printInt(value);
	printFloat(value);
	printDouble(value);
}
