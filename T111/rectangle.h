#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.h"

class Rectangle : public Shape
{
public:
  Rectangle(point_t pLeft, point_t pRight);
  Rectangle(rectangle_t rectangle);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(const point_t& newpos) override;
  void scale(double ratio) override;
  Shape* clone() const override;

private:
  rectangle_t rectangle;
};

#endif
