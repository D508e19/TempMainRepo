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

    int arriveAtTick =-1;

    void AddWayPoint(Coordinate newCoord, Coordinate lastCord);
    Coordinate GetNextWaypoint();   
};


#endif