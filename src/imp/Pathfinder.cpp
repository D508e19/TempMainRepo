#ifndef PATHFINDER_CPP
#define PATHFINDER_CPP

Pathfinder::Pathfinder(){}
Pathfinder::~Pathfinder(){}

Path Pathfinder::GetStupidPath(Coordinate start, Coordinate end)
{
    //std::cout << "From: " << start.x << ", " << start.y << std::endl;
    //std::cout << "Want to go to: " << end.x << ", " << end.y << std::endl;
   
    Path newPath;

    newPath.AddWayPoint(Coordinate(end.x, start.y), start);
    newPath.AddWayPoint(Coordinate(end.x, end.y), Coordinate(end.x, start.y));

    return newPath;
}


#endif