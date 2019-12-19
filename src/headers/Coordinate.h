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

    bool operator == (Coordinate& c) { return c.x == x && c.y == y; }
    Coordinate operator + (Coordinate& c) { return Coordinate( c.x + x, c.y + y ); }
};


#endif