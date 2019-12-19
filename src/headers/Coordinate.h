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

    bool operator ==( const Coordinate& o ) { return o.x == x && o.y == y; }
    Coordinate operator +( const Coordinate& o ) { return Coordinate( o.x + x, o.y + y ); }
};


#endif