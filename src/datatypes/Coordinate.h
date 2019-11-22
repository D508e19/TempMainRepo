#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate
{
private:

public:
    Coordinate();
    Coordinate(int x, int y);
    ~Coordinate();

    int x;
    int y;

    void PrintCoordinate();
};

Coordinate::Coordinate(){}
Coordinate::Coordinate(int px, int py):x(px), y(py){}
Coordinate::~Coordinate(){}


void Coordinate::PrintCoordinate(){
    std::cout << "(" << x << ", " << y << ")" << std::endl;    
}

#endif