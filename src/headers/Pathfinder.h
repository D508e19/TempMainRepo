#ifndef PATHFINDER_H
#define PATHFINDER_h

typedef std::list<std::pair<Coordinate, Coordinate>> simplePath;

class Pathfinder
{
private:
    int selectedAlgorithm;

    bool ReserveTimeslotsForPath(int startTick, Path path);


    EnvironmentManager* environmentManager;


    Path ReversePath(Node node);
    simplePath ConstructPath(Node, simplePath);

    // data collection
    int pathReturnedEmpty = 0;

public:
    EnvironmentManager* em;

    Pathfinder(EnvironmentManager* _em);
    ~Pathfinder();
   
    Path FindPath(int startTick, Coordinate start, Coordinate end, direction last, bool isCarrying);

    Path GetStupidPath(Coordinate start, Coordinate end);
    Path GetAstarPath(int startTick, Coordinate start, Coordinate end, direction last, bool isCarrying, EnvironmentManager* _environmentManager, int straightTime = 20, int turnTime = 20, int waitTime = 5);
};


#endif