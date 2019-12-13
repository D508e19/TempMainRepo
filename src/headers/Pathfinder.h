#ifndef PATHFINDER_H
#define PATHFINDER_h

typedef std::list<std::pair<Coordinate, Coordinate>> simplePath;

class Pathfinder
{
private:
    int selectedAlgorithm;

    int ReserveTimeslotsForPath(int startTick, direction startDirection, Coordinate startCoord, Path path);
    
    Path GetStupidPath(Coordinate start, Coordinate end);
    Path GetAstarPath(Coordinate start, Coordinate end, direction last, bool isCarrying);

    Node* currentNode;
    Path pathList;

    Path ReversePath(Node node, Path path);
    simplePath ConstructPath(Node, simplePath);

    int ticksToMoveOneCell = 20;
    int ticksToTurn90degrees = 20;
    int ticksToTurn180degrees = 40;
    int ticksToPickUpPod = 20;
    int ticksToPutDownPod = 20;
    int ticksToPickAtPickingST = 50;

    // data collection    
    int pathReturnedEmpty = 0;
        
public:
    Pathfinder(EnvironmentManager* _em);
    ~Pathfinder();
   
    EnvironmentManager* em;

    Path FindPath(int startTick, Coordinate start, Coordinate end, direction last, bool isCarrying);

};


#endif