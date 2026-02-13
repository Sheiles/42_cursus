#include <iostream>
#include "Point.hpp"
#include "Fixed.hpp"

bool bsp(Point const a, Point const b, Point const c, Point const point);

int main(void)
{
	Point a(0.0f, 0.0f);
	Point b(10.0f, 0.0f);
	Point c(5.0f, 10.0f);

	// Test point inside the triangle
	Point p1(5.0f, 5.0f);
	if (bsp(a, b, c, p1))
		std::cout << "Point 1 (5, 5) is inside the triangle" << std::endl;
	else
		std::cout << "Point 1 (5, 5) is NOT inside the triangle" << std::endl;

	// Test point outside the triangle
	Point p2(0.0f, 5.0f);
	if (bsp(a, b, c, p2))
		std::cout << "Point 2 (0, 5) is inside the triangle" << std::endl;
	else
		std::cout << "Point 2 (0, 5) is NOT inside the triangle" << std::endl;

	// Test point on a vertex
	Point p3(0.0f, 0.0f);
	if (bsp(a, b, c, p3))
		std::cout << "Point 3 (0, 0) is inside the triangle" << std::endl;
	else
		std::cout << "Point 3 (0, 0) is NOT inside the triangle" << std::endl;

	return 0;
}
