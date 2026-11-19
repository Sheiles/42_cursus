// Compile:
// c++ -Wall -Wextra -Werror -std=c++98 -I my_solution main.cpp my_solution/vect2.cpp -o vect2
// c++ -Wall -Wextra -Werror -std=c++98 -I short main.cpp short/vect2.cpp -o vect2

#pragma once
#include <iostream>

class vect2
{
	int v[2];

public:
	vect2(int x = 0, int y = 0) { v[0] = x; v[1] = y; }

	int &operator[](int i) { return v[i]; }
	int operator[](int i) const { return v[i]; }

	vect2 &operator+=(const vect2 &o) { v[0] += o.v[0]; v[1] += o.v[1]; return *this; }
	vect2 &operator-=(const vect2 &o) { v[0] -= o.v[0]; v[1] -= o.v[1]; return *this; }
	vect2 &operator*=(int n) { v[0] *= n; v[1] *= n; return *this; }

	vect2 operator+(const vect2 &o) const { return vect2(*this) += o; }
	vect2 operator-(const vect2 &o) const { return vect2(*this) -= o; }
	vect2 operator*(int n) const { return vect2(*this) *= n; }
	vect2 operator-() const { return vect2(-v[0], -v[1]); }

	vect2 &operator++() { return *this += vect2(1, 1); }
	vect2 &operator--() { return *this -= vect2(1, 1); }
	vect2 operator++(int) { vect2 t(*this); ++*this; return t; }
	vect2 operator--(int) { vect2 t(*this); --*this; return t; }

	bool operator==(const vect2 &o) const { return v[0] == o.v[0] && v[1] == o.v[1]; }
	bool operator!=(const vect2 &o) const { return !(*this == o); }
};

vect2 operator*(int n, const vect2 &v);
std::ostream &operator<<(std::ostream &os, const vect2 &v);