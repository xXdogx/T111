#include "concave.h"
#include <stdexcept>
#include <algorithm>

Concave::Concave(point_t p1, point_t p2, point_t p3, point_t pInner) :
  positions{ p1, p2, p3, pInner }
{
  if (isConcave(positions[0], positions[1], positions[2], positions[3]))
  {
    throw std::invalid_argument("Error: invalid concave parameters");
  }
}

std::array< double, 6 > Concave::splitIntoTriangles() const
{
  double a1_ = calcPointsDistance(positions[0], positions[2]);
  double b1_ = calcPointsDistance(positions[2], positions[1]);
  double c1_ = calcPointsDistance(positions[0], positions[1]);
  double a2_ = calcPointsDistance(positions[2], positions[3]);
  double b2_ = b1_;
  double c2_ = calcPointsDistance(positions[3], positions[1]);
  std::array< double, 6 > arr = { a1_, b1_, c1_, a2_, b2_, c2_ };
  return arr;
}

double Concave::getArea() const
{
  std::array< double, 6 > sides = splitIntoTriangles();
  double a1 = sides[0];
  double b1 = sides[1];
  double c1 = sides[2];
  double a2 = sides[3];
  double b2 = sides[4];
  double c2 = sides[5];
  return calculateTriangleArea(a1, b1, c1) - calculateTriangleArea(a2, b2, c2);
}

rectangle_t Concave::getFrameRect() const
{
  double up = std::max({ positions[0].y, positions[1].y, positions[2].y });
  double down = std::min({ positions[0].y, positions[1].y, positions[2].y });
  double left = std::min({ positions[0].x, positions[1].x, positions[2].x });
  double right = std::max({ positions[0].x, positions[1].x, positions[2].x });
  return { right - left, up - down, {(right + left) / 2, (up + down) / 2} };
}

void Concave::move(const point_t& pos)
{
  point_t delta = { pos.x - getFrameRect().pos.x, pos.y - getFrameRect().pos.y };
  move(delta.x, delta.y);
}

void Concave::move(double dx, double dy)
{
  for (point_t& position : positions)
  {
    position.x += dx;
    position.y += dy;
  }
}

void Concave::scale(double ratio)
{
  point_t center = getFrameRect().pos;
  for (point_t& position : positions)
  {
    position = calculateScale(position, center, ratio);
  }
}