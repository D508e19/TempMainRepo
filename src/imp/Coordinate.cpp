#ifndef COORDINATE_CPP
#define COORDINATE_CPP

Coordinate::Coordinate(){}
Coordinate::Coordinate(int px, int py):x(px), y(py){}
Coordinate::~Coordinate(){}

void Coordinate::PrintCoordinate(){
    argos::LOG << "(" << x << ", " << y << ")"; // << std::endl;
}

#endif