#ifndef CONCAVE_HPP
#define CONCAVE_HPP
#include <array>
#include "shape.h"

class Concave : public Shape
{
public:
  Concave(point_t p1, point_t p2, point_t p3, point_t pInner);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& newpos) override;
  void move(double dx, double dy) override;
  void scale(double ratio) override;
  Shape* clone() const override;
private:
  point_t positions[4];
  std::array< double, 6 > splitIntoTriangles() const;
};

#endif
