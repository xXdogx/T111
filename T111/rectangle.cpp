#include <stdexcept>
#include "rectangle.h"

Rectangle::Rectangle(point_t pLeft, point_t pRight) :
  rectangle({ pRight.x - pLeft.x, pRight.y - pLeft.y, {(pLeft.x + pRight.x) / 2.0, (pLeft.y + pRight.y) / 2.0} })
{
  if (rectangle.width <= 0.0 || rectangle.height <= 0.0)
  {
    throw std::invalid_argument("ERROR! Invalid rectangle points");
  }
}

Rectangle::Rectangle(rectangle_t rectangle) :
  rectangle(rectangle)
{}

double Rectangle::getArea() const
{
  return rectangle.width * rectangle.height;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle;
}

void Rectangle::move(const double dx, const double dy)
{
  rectangle.pos.x += dx;
  rectangle.pos.y += dy;
}

void Rectangle::move(const point_t& newpos)
{
  rectangle.pos = newpos;
}

void Rectangle::scale(const double ratio)
{
  if (ratio <= 0.0)
  {
    throw std::invalid_argument("Invalid scale ratio");
  }
  rectangle.width *= ratio;
  rectangle.height *= ratio;
}

Shape* Rectangle::clone() const
{
  return new Rectangle(rectangle.pos, r1, r2);
}