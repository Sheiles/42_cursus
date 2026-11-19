/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_short.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 11:01:24 by brrr1             #+#    #+#             */
/*   Updated: 2026/10/29 11:01:35 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <string>

class bigint
{
	std::string s;

public:
	bigint(unsigned long n = 0) { std::ostringstream o; o << n; s = o.str(); }

	bigint &operator+=(const bigint &o);
	bigint operator+(const bigint &o) const { return bigint(*this) += o; }
	bigint &operator++() { return *this += 1; }
	bigint operator++(int) { bigint t(*this); ++*this; return t; }

	bigint &operator<<=(const bigint &n);
	bigint &operator>>=(const bigint &n);
	bigint operator<<(const bigint &n) const { return bigint(*this) <<= n; }
	bigint operator>>(const bigint &n) const { return bigint(*this) >>= n; }

	bool operator<(const bigint &o) const
	{
		return s.size() != o.s.size() ? s.size() < o.s.size() : s < o.s;
	}
	bool operator>(const bigint &o) const { return o < *this; }
	bool operator<=(const bigint &o) const { return !(o < *this); }
	bool operator>=(const bigint &o) const { return !(*this < o); }
	bool operator==(const bigint &o) const { return s == o.s; }
	bool operator!=(const bigint &o) const { return s != o.s; }

	const std::string &str() const { return s; }
};

std::ostream &operator<<(std::ostream &os, const bigint &b);