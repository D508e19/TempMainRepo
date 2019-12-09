#ifndef PATHFINDER_H
#define PATHFINDER_h

typedef std::list<std::pair<Coordinate, Coordinate>> simplePath;

class Pathfinder
{
private:
    int selectedAlgorithm;

    EnvironmentManager* em;

    bool ReserveTimeslotsForPath(int startTick, Path path);


    int pathReturnedEmpty = 0;

    Node* currentNode;
    Path pathList;
    EnvironmentManager* environmentManager;


    Path ReversePath(Node node, Path path);
    simplePath ConstructPath(Node, simplePath);

    // data collection
    int pathReturnedEmpty = 0;

public:
    Pathfinder(EnvironmentManager* _em);
    ~Pathfinder();
   
    Path FindPath(Coordinate start, Coordinate end, direction last, bool isCarrying);

    Path GetStupidPath(Coordinate start, Coordinate end);
    Path GetAstarPath(Coordinate start, Coordinate end, direction last, bool isCarrying, EnvironmentManager* _environmentManager, int straightTime = 2, int turnTime = 2, int waitTime = 1);
};


#endif