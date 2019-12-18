#ifndef PATH_CPP
#define PATH_CPP

#include <queue>

Path::Path(){}
Path::~Path(){}

void Path::AddWayPoint(Coordinate newCord, Coordinate lastCoord)
{
    int xLast = lastCoord.x;
    int yLast = lastCoord.y;

    if(xLast == newCord.x && yLast == newCord.y)
        {
            //todo ERROR message
            return;
        }

    waypoints.push(newCord);   
}

Coordinate Path::GetNextWaypoint()
{
    Coordinate nextWaypoint = waypoints.front();
    waypoints.pop();
    return nextWaypoint;
}


#endif