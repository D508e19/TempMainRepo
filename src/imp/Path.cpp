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