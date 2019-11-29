#ifndef PATHFINDER_H
#define PATHFINDER_h

class Pathfinder
{
private:
    int selectedAlgorithm;
        
public:
    Pathfinder();
    ~Pathfinder();
   
    Path FindPath(Coordinate start, Coordinate end);

    Path GetStupidPath(Coordinate start, Coordinate end);
};


#endif