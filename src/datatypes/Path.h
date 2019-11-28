#ifndef PATH_H
#define PATH_H

#include <queue>

#include "Coordinate.h"

class Path
{
private:

public:
    Path();
    ~Path();

    std::queue <Coordinate> waypoints;

    void AddWayPoint(Coordinate newCoord, Coordinate lastCord);
    Coordinate GetNextWaypoint();   
};

Path::Path(){}
Path::~Path(){}

void Path::AddWayPoint(Coordinate newCord, Coordinate lastCoord)
{
    int xLast = lastCoord.x;
    int yLast = lastCoord.y;

    if(xLast == newCord.x && yLast == newCord.y)
        {
            //std::cout << "dublicate waypoint. " << newCord.x << " " << newCord.y << " .Ignored" << std::endl;
            return;
        }

    //std::cout << "Adding waypoint:" << newCord.x << " " << newCord.y << std::endl;
    waypoints.push(newCord);   
}

Coordinate Path::GetNextWaypoint()
{
    Coordinate nextWaypoint = waypoints.front();
    waypoints.pop();
    return nextWaypoint;
}


#endif