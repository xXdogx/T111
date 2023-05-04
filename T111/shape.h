#ifndef SHAPE_H
#define SHAPE_H
#include <iosfwd>
#include "base-types.h"

class Shape
{
public:
  virtual ~Shape() = default;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(double dx, double dy) = 0;
  virtual void move(const point_t& pos) = 0;
  virtual void scale(double ratio) = 0;
};

#endif
