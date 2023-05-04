#ifndef RING_H
#define RING_H
#include "base-types.h"
#include "shape.h"
#include "rectangle.h"

class Ring : public Shape
{
public:
  Ring(point_t midle, double first, double second);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& newpos) override;
  void move(double delta_x, double delta_y) override;
  void scale(double k) override;
  Shape* clone() const override;
private:
  rectangle_t rectangle;
  double r1, r2;
};

#endif 
