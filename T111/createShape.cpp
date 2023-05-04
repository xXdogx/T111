#include <stdexcept>
#include "createShape.h"
#include "rectangle.h"
#include "concave.h"

double* checkInputArray(std::istream& input, double* poss, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    input >> poss[i];
    if (!input)
    {
      throw std::invalid_argument("ERROR! Invalid argument");
    }
  }
  return poss;
}

Shape* createRectangle(std::istream& input)
{
  double poss[4]{};
  checkInputArray(input, poss, 4);
  return new Rectangle({poss[0], poss[1]}, {poss[2], poss[3]});
}

Shape* createConcave(std::istream& input)
{
  double poss[8]{};
  checkInputArray(input, poss, 8);
  return new Concave({poss[0], poss[1]}, {poss[2], poss[3]}, {poss[4], poss[5]}, {poss[6], poss[7]});
}

scale_t getScale(std::istream& input)
{
  double poss[3]{};
  checkInputArray(input, poss, 3);
  if (poss[2] < 0.0)
  {
    throw std::invalid_argument("ERROR! Invalid scale size");
  }
  return { {poss[0], poss[1]}, poss[2]};
}