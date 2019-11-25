#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <environment/pathfinding/aStar.h>
#include "src/datatypes/Coordinate.h"
#include "src/datatypes/Path.h"
#include "src/datatypes/direction"

class Pathfinder
{
private:
    
    
public:
    Pathfinder();
    Pathfinder(Coordinate);
    ~Pathfinder();
    aStar astar = aStar();

    Path GetStupidPath(Coordinate start, Coordinate end);
};

Pathfinder::Pathfinder(){}
Pathfinder::~Pathfinder(){}

Path Pathfinder::GetStupidPath(Coordinate start, Coordinate end)
{
    std::mutex mtx;

    Path newPath;
//    //argos::LOG << "Find path to: ";
//    //end.PrintCoord();
//    std::cout << "Want to go to: " << end.x << ", " << end.y << std::endl;
//    //std::cout << "Adding waypoint:" << start.x << " " << start.y << std::endl;
//    //newPath.AddWayPoint(start);
//    std::cout << "Adding waypoint:" << end.x << " " << start.y << std::endl;
//    newPath.AddWayPoint(Coordinate(end.x, start.y), start);
//    std::cout << "Adding waypoint:" << end.x << " " << end.y << std::endl;
//    newPath.AddWayPoint(Coordinate(end.x, end.y), Coordinate(end.x, start.y));
//
    newPath = this->astar.pathFinder(start, north, end);
    return newPath;
    //return this->astar.pathFinder(start, north, end);
}


#endif