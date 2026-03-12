#include "Point.hpp"
#include "Fixed.hpp"


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

	
	return (areaABC == (areaABP + areaACP + areaBCP));
}
