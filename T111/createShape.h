#ifndef CREATE_SHAPE_HPP
#define CREATE_SHAPE_HPP
#include <istream>
#include <array>
#include <cstddef>
#include "shape.h"

double* checkInputArray(std::istream& input, double* poss, size_t size);
Shape* createRectangle(std::istream& input);
Shape* createConcave(std::istream& input);
Shape* createDiamond(std::istream& input);
scale_t getScale(std::istream& input);

#endif
