#include <cmath>
#include "base-types.h"

double calcPointsDistance(const point_t& p1, const point_t& p2)
{
  double line_x = p1.x - p2.x;
  double line_y = p1.y - p2.y;
  return std::sqrt(line_x * line_x + line_y * line_y);
}

point_t calculateVectorSum(point_t pos, double dx, double dy)
{
  pos.x += dx;
  pos.y += dy;
  return pos;
}

point_t calculateVectorDifference(point_t pos, double dx, double dy)
{
  return calculateVectorSum(pos, -dx, -dy);
}

point_t multiplicationVector(point_t pos, double ratio)
{
  pos.x *= ratio;
  pos.y *= ratio;
  return pos;
}

point_t calculateScale(point_t pos, point_t center, double ratio)
{
  return calculateVectorSum(multiplicationVector(calculateVectorDifference(pos, center.x, center.y), ratio), center.x, center.y);
}

double calculateTriangleArea(const double& a, const double& b, const double& c)
{
  double p = (a + b + c) / 2;
  return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

bool checkPosSide(const point_t& p1, const point_t& p2, const point_t& p0)
{
  return ((p1.x - p0.x) * (p2.y - p1.y) - (p2.x - p1.x) * (p1.y - p0.y)) > 0;
}

bool isTriangle(const point_t& p1, const point_t& p2, const point_t& p3)
{
  double a = calcPointsDistance(p3, p1);
  double b = calcPointsDistance(p2, p1);
  double c = calcPointsDistance(p3, p2);
  return a + b < c || a + c < b || b + c < a;
}

bool isPointInsideTriangle(const point_t& p1, const point_t& p2, const point_t& p3, const point_t& pInner)
{
  bool triangle1 = checkPosSide(p1, p2, pInner);
  bool triangle2 = checkPosSide(p2, p3, pInner);
  bool triangle3 = checkPosSide(p3, p1, pInner);;
  return !((triangle1 && triangle2 && triangle3) || (!triangle1 && !triangle2 && !triangle3));
}

bool isConcave(const point_t& p1, const point_t& p2, const point_t& p3, const point_t& pInner)
{
  return (isTriangle(p1, p2, p3) || p1.x == pInner.x || p1.y == pInner.y || isPointInsideTriangle(p1, p2, p3, pInner));
}

point_t calcPosXY(point_t pos, point_t center)
{
  return { pos.x - (pos.x - center.x) * 2.0, pos.y - (pos.y - center.y) * 2.0 };
}