#include <iostream>
#include <iomanip>
#include "base-types.h"
#include "createShape.h"

Shape** expandShapesArr(Shape** shapes, size_t& capacity)
{
  capacity *= 2;
  Shape** newShapes = new Shape * [capacity];
  for (size_t i = 0; i < capacity; i++)
  {
    newShapes[i] = shapes[i];
  }
  return newShapes;
}

void deleteShapesArr(Shape** shapes, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    delete shapes[i];
  }
  delete[] shapes;
}

std::ostream& outputData(std::ostream& out, const Shape* const* shapes, const size_t size)
{
  double sumArea = 0.0;
  for (size_t i = 0; i < size; i++)
  {
    sumArea += shapes[i]->getArea();
  }
  out << std::fixed << std::setprecision(1) << sumArea;
  double leftBottomX = 0.0;
  double leftBottomY = 0.0;
  double rightTopX = 0.0;
  double rightTopY = 0.0;
  for (size_t i = 0; i < size; i++)
  {
    leftBottomX = shapes[i]->getFrameRect().pos.x - shapes[i]->getFrameRect().width / 2;
    leftBottomY = shapes[i]->getFrameRect().pos.y - shapes[i]->getFrameRect().height / 2;
    rightTopX = shapes[i]->getFrameRect().pos.x + shapes[i]->getFrameRect().width / 2;
    rightTopY = shapes[i]->getFrameRect().pos.y + shapes[i]->getFrameRect().height / 2;
    out << " " << leftBottomX << " " << leftBottomY << " " << rightTopX << " " << rightTopY;
  }
  out << "\n";
  return out;
}

void movePointBecauseOfScale(point_t& p, const point_t& zoomCenter, double k)
{
  p.x += (p.x - zoomCenter.x) * (k - 1.0);
  p.y += (p.y - zoomCenter.y) * (k - 1.0);
}

void fullScale(Shape* shape, const point_t& zoomCenter, double ratio)
{
  point_t a1;
  a1.x = shape->getFrameRect().pos.x - shape->getFrameRect().width / 2;
  a1.y = shape->getFrameRect().pos.y - shape->getFrameRect().height / 2;
  shape->move(zoomCenter);
  point_t a2;
  a2.x = shape->getFrameRect().pos.x - shape->getFrameRect().width / 2;
  a2.y = shape->getFrameRect().pos.y - shape->getFrameRect().height / 2;
  double dx = a1.x - a2.x;
  double dy = a1.y - a2.y;
  shape->scale(ratio);
  movePointBecauseOfScale(a2, zoomCenter, ratio);
  shape->move(ratio * dx, ratio * dy);
}

int main()
{
  bool isScale = false;
  bool isAdded = false;
  scale_t scale = { {0.0, 0.0}, 0.0 };
  std::string input = " ";

  size_t size = 0;
  size_t capacity = 10;
  Shape** shapes = new Shape * [capacity];

  while (std::cin)
  {
    std::cin >> input;
    try
    {
      if (size == capacity)
      {
        Shape** newShapes = expandShapesArr(shapes, capacity);
        delete[] shapes;
        shapes = newShapes;
      }
      if (input == "RECTANGLE")
      {
        shapes[size] = createRectangle(std::cin);
        isAdded = true;
      }
      if (input == "CONCAVE")
      {
        shapes[size] = createConcave(std::cin);
        isAdded = true;
      }
      if (isAdded)
      {
        size++;
        isAdded = false;
      }
      if (input == "SCALE")
      {
        scale = getScale(std::cin);
        if (size > 0)
        {
          isScale = true;
        }
        break;
      }
    }

    catch (const std::invalid_argument& e)
    {
      std::cerr << e.what() << '\n';
    }
    catch (...)
    {
      std::cerr << "\nERROR! An error occurred while working with shapes\n";
      deleteShapesArr(shapes, size);
      return 2;
    }
  }

  if (isScale)
  {
    outputData(std::cout, shapes, size);
    try
    {
      for (size_t i = 0; i < size; i++)
      {
        fullScale(shapes[i], scale.pos, scale.scale);
      }
    }
    catch (const std::invalid_argument& e)
    {
      std::cerr << e.what();
      deleteShapesArr(shapes, size);
      return 2;
    }
    outputData(std::cout, shapes, size);
    deleteShapesArr(shapes, size);
  }
  else
  {
    std::cerr << "ERROR! No SCALE command";
    deleteShapesArr(shapes, size);
    return 2;
  }
  return 0;
}