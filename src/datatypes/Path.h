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

    void AddWayPoint(Coordinate newCoord);
    Coordinate GetNextWaypoint();
    
};

Path::Path(){}
Path::~Path(){}

//check om nyt wp er somme koordinat som sidste koor. hvis så ignorer
void Path::AddWayPoint(Coordinate newCord)
{
    if(waypoints.empty())
    {
        waypoints.push(newCord);

        return;
    }

    int xLast = waypoints.back().x;
    int yLast = waypoints.back().y;

    std::cout << xLast << "," << yLast << " -> "<< newCord.x << " , " << newCord.y << std::endl;
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