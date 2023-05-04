#include "ring.h"
#include "rectangle.h"

Ring::Ring(point_t midle, double first, double second) :
	rectangle({first * 2.0, first * 2.0, midle}),
	r1(first),
	r2(second)
{
}

double Ring::getArea() const
{
	return r1 * r1 * 3.1415926 - r2 * r2 * 3.1415926;
}

rectangle_t Ring::getFrameRect() const
{
	return rectangle;
}

void Ring::move(const point_t& newpos)
{
	rectangle.pos = newpos;
}

void Ring::move(double delta_x, double delta_y)
{
	rectangle.pos = calculateVectorSum(rectangle.pos, delta_x, delta_y);
}

void Ring::scale(double k)
{
	r1 *= k;
	r2 *= k;
	rectangle.width = r1 * 2.0;
	rectangle.height = r1 * 2.0;
}

Shape* Ring::clone() const
{
	return new Ring(rectangle.pos, r1, r2);
}