#ifndef BASE_TYPES_H
#define BASE_TYPES_H

struct point_t
{
  double x, y;
};

struct rectangle_t
{
  double width, height;
  point_t pos;
};

struct scale_t
{
  point_t pos;
  double scale;
};

double calcPointsDistance(const point_t& p1, const point_t& p2);
point_t calcPosXY(point_t pos, point_t center);
point_t calculateVectorSum(point_t position, double dx, double dy);
point_t calculateVectorDifference(point_t position, double dx, double dy);
point_t calculateScale(point_t pos, point_t center, double ratio);
point_t multiplicationVector(point_t pos, double ratio);
double calculateTriangleArea(const double& a, const double& b, const double& c);
bool checkPosSide(const point_t& p1, const point_t& p2, const point_t& p0);
bool isTriangle(const point_t& p1, const point_t& p2, const point_t& p3);
bool isPointInsideTriangle(const point_t& p1, const point_t& p2, const point_t& p3, const point_t& pInner);
bool isConcave(const point_t& p1, const point_t& p2, const point_t& p3, const point_t& pInner);

#endif
