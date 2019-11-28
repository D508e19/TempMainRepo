#ifndef PATHFINDER_H
#define PATHFINDER_h

class Pathfinder
{
private:
        
public:
    Pathfinder();
    ~Pathfinder();
   
    Path GetStupidPath(Coordinate start, Coordinate end);
};


#endif