/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_short.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 11:02:00 by brrr1             #+#    #+#             */
/*   Updated: 2026/10/29 11:02:03 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.hpp"

static unsigned long to_ul(const std::string &s)
{
	unsigned long n = 0;
	std::istringstream(s) >> n;
	return n;
}

bigint &bigint::operator+=(const bigint &o)
{
	std::string r;
	int i = s.size() - 1, j = o.s.size() - 1, c = 0;

	while (i >= 0 || j >= 0 || c)
	{
		if (i >= 0) c += s[i--] - '0';
		if (j >= 0) c += o.s[j--] - '0';
		r.insert(r.begin(), char('0' + c % 10));
		c /= 10;
	}
	s = r;
	return *this;
}

bigint &bigint::operator<<=(const bigint &n)
{
	if (s != "0")
		s.append(to_ul(n.s), '0');
	return *this;
}

bigint &bigint::operator>>=(const bigint &n)
{
	unsigned long k = to_ul(n.s);
	s = k >= s.size() ? "0" : s.substr(0, s.size() - k);
	return *this;
}

std::ostream &operator<<(std::ostream &os, const bigint &b)
{
	return os << b.str();
}