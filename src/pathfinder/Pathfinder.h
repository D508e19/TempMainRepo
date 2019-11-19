#ifndef PATHFINDER_H
#define PATHFINDER_h

#include "src/datatypes/Coordinate.h"
#include "src/datatypes/Path.h"

class Pathfinder
{
private:
    
    
public:
    Pathfinder();
    Pathfinder(Coordinate);
    ~Pathfinder();
   
    Path GetStupidPath(Coordinate start, Coordinate end);
};

Pathfinder::Pathfinder(){}
Pathfinder::~Pathfinder(){}

Path Pathfinder::GetStupidPath(Coordinate start, Coordinate end)
{
    //argos::LOG << "Find path to: "; 
    //end.PrintCoord();
    std::cout << "Want to go to: " << end.x << ", " << end.y << std::endl;
    Path newPath;
    newPath.AddWayPoint(start);
    newPath.AddWayPoint(Coordinate(end.x, start.y));
    newPath.AddWayPoint(Coordinate(end.x, end.y));

    return newPath;
}


#endif