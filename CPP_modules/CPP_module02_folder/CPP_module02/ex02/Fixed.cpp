#include "Fixed.hpp"
#include <iostream>
#include <cmath>

Fixed::Fixed(void) : _value(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int n)
{
	std::cout << "Int constructor called" << std::endl;
	this->_value = n << this->_frac_bits;
}

Fixed::Fixed(const float f)
{
	std::cout << "Float constructor called" << std::endl;
	this->_value = roundf(f * (1 << this->_frac_bits));
}

Fixed::Fixed(const Fixed &copy)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = copy;
}

Fixed &Fixed::operator=(const Fixed &rhs)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &rhs)
		this->_value = rhs.getRawBits();
	return *this;
}

Fixed::~Fixed(void)
{
	std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const
{
	return this->_value;
}

void Fixed::setRawBits(int const raw)
{
	this->_value = raw;
}

float Fixed::toFloat(void) const
{
	return (float)this->_value / (1 << this->_frac_bits);
}

int Fixed::toInt(void) const
{
	return this->_value >> this->_frac_bits;
}

// Comparison operators
bool Fixed::operator>(const Fixed &rhs) const
{
	return this->_value > rhs.getRawBits();
}

bool Fixed::operator<(const Fixed &rhs) const
{
	return this->_value < rhs.getRawBits();
}

bool Fixed::operator>=(const Fixed &rhs) const
{
	return this->_value >= rhs.getRawBits();
}

bool Fixed::operator<=(const Fixed &rhs) const
{
	return this->_value <= rhs.getRawBits();
}

bool Fixed::operator==(const Fixed &rhs) const
{
	return this->_value == rhs.getRawBits();
}

bool Fixed::operator!=(const Fixed &rhs) const
{
	return this->_value != rhs.getRawBits();
}

// Arithmetic operators
Fixed Fixed::operator+(const Fixed &rhs) const
{
	Fixed result;
	result.setRawBits(this->_value + rhs.getRawBits());
	return result;
}

Fixed Fixed::operator-(const Fixed &rhs) const
{
	Fixed result;
	result.setRawBits(this->_value - rhs.getRawBits());
	return result;
}

Fixed Fixed::operator*(const Fixed &rhs) const
{
	Fixed result;
	result.setRawBits((this->_value * rhs.getRawBits()) >> this->_frac_bits);
	return result;
}

Fixed Fixed::operator/(const Fixed &rhs) const
{
	Fixed result;
	result.setRawBits((this->_value << this->_frac_bits) / rhs.getRawBits());
	return result;
}

// Increment/Decrement operators
Fixed &Fixed::operator++(void)
{
	this->_value++;
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed tmp(*this);
	++(*this);
	return tmp;
}

Fixed &Fixed::operator--(void)
{
	this->_value--;
	return *this;
}

Fixed Fixed::operator--(int)
{
	Fixed tmp(*this);
	--(*this);
	return tmp;
}

// Static member functions
Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	return (a < b) ? a : b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
	return (a < b) ? a : b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	return (a > b) ? a : b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
	return (a > b) ? a : b;
}

std::ostream &operator<<(std::ostream &os, const Fixed &fixed)
{
	os << fixed.toFloat();
	return os;
}
