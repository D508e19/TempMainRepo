#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate
{
public:
    Coordinate();
    Coordinate(int x, int y);
    ~Coordinate();

    int x{};
    int y{};

    //void PrintCoordinate();
};

Coordinate::Coordinate()= default;
Coordinate::Coordinate(int px, int py):x(px), y(py){}
Coordinate::~Coordinate()= default;


//void Coordinate::PrintCoordinate(){
//    std::cout << "(" << x << ", " << y << ")" << std::endl;
//}

#endif //KBOT_COORDINATE_H

