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


#endif