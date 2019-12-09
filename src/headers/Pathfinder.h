#ifndef PATHFINDER_H
#define PATHFINDER_h

typedef std::list<std::pair<Coordinate, Coordinate>> simplePath;

class Pathfinder
{
private:
    int selectedAlgorithm;

    int pathReturnedEmpty = 0;

    Node* currentNode;
    Path pathList;
    
    Path ReversePath(Node node, Path path);
    simplePath ConstructPath(Node, simplePath);
    EnvironmentManager* environmentManager;
        
public:
    Pathfinder();
    ~Pathfinder();
   
    Path FindPath(Coordinate start, Coordinate end, direction last, bool isCarrying, EnvironmentManager* _environmentManager);

    Path GetStupidPath(Coordinate start, Coordinate end);
    Path GetAstarPath(Coordinate start, Coordinate end, direction last, bool isCarrying, EnvironmentManager* _environmentManager, int straightTime = 2, int turnTime = 2, int waitTime = 1);
};


#endif