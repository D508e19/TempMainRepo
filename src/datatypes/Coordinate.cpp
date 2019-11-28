
#include <stdlib.h>

#include "Coordinate.h"

Coordinate::Coordinate() {}
Coordinate::Coordinate(int px, int py) : x(px), y(py) {}
Coordinate::~Coordinate() {}

void Coordinate::PrintCoordinate()
{
    std::cout << "(" << x << ", " << y << ")" << std::endl;
}
