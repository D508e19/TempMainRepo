#ifndef PATH_H
#define PATH_H

#include <queue>

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


#endif