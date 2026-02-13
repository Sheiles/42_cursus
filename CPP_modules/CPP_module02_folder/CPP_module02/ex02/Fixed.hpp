#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed
{
private:
	int _value;
	static const int _frac_bits = 8;

public:
	Fixed(void);
	Fixed(const int n);
	Fixed(const float f);
	Fixed(const Fixed &copy);
	Fixed &operator=(const Fixed &rhs);
	~Fixed(void);

	int getRawBits(void) const;
	void setRawBits(int const raw);
	float toFloat(void) const;
	int toInt(void) const;

	// Comparison operators
	bool operator>(const Fixed &rhs) const;
	bool operator<(const Fixed &rhs) const;
	bool operator>=(const Fixed &rhs) const;
	bool operator<=(const Fixed &rhs) const;
	bool operator==(const Fixed &rhs) const;
	bool operator!=(const Fixed &rhs) const;

	// Arithmetic operators
	Fixed operator+(const Fixed &rhs) const;
	Fixed operator-(const Fixed &rhs) const;
	Fixed operator*(const Fixed &rhs) const;
	Fixed operator/(const Fixed &rhs) const;

	// Increment/Decrement operators
	Fixed &operator++(void);			// pre-increment
	Fixed operator++(int);				// post-increment
	Fixed &operator--(void);			// pre-decrement
	Fixed operator--(int);				// post-decrement

	// Static member functions
	static Fixed &min(Fixed &a, Fixed &b);
	static const Fixed &min(const Fixed &a, const Fixed &b);
	static Fixed &max(Fixed &a, Fixed &b);
	static const Fixed &max(const Fixed &a, const Fixed &b);
};

std::ostream &operator<<(std::ostream &os, const Fixed &fixed);

#endif
