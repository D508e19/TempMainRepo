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

    if(waypoints.empty())
    {
        std::cout << xLast << "," << yLast << " -> "<< newCord.x << ", " << newCord.y << std::endl;
        waypoints.push(newCord);
        return;
    }



    std::cout << xLast << "," << yLast << " -> "<< newCord.x << ", " << newCord.y << std::endl;
    {
        if(xLast == newCord.x && yLast == newCord.y)
            {
                argos::LOG << "nope" << std::endl;
                return;
            }
        argos::LOG << "ok" << std::endl;
        waypoints.push(newCord);
    }    
}

Coordinate Path::GetNextWaypoint()
{
    Coordinate nextWaypoint = waypoints.front();
    waypoints.pop();
    return nextWaypoint;
}


#endif