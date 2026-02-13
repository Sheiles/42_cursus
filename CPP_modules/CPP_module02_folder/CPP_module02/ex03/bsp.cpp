#include "Point.hpp"
#include "Fixed.hpp"

// Function to compute the area of a triangle given three points
static Fixed computeArea(Point const a, Point const b, Point const c)
{
	Fixed area;

	area = ((a.getX() * (b.getY() - c.getY())
		+ b.getX() * (c.getY() - a.getY())
		+ c.getX() * (a.getY() - b.getY())) / Fixed(2));

	if (area < Fixed(0))
		area = area * Fixed(-1);

	return area;
}

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed areaABC = computeArea(a, b, c);
	Fixed areaABP = computeArea(a, b, point);
	Fixed areaACP = computeArea(a, c, point);
	Fixed areaBCP = computeArea(b, c, point);

	// If point is inside the triangle, sum of sub-areas should equal the main area
	return (areaABC == (areaABP + areaACP + areaBCP));
}
