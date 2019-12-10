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
        
public:
    Pathfinder(EnvironmentManager* _em);
    ~Pathfinder();
   
    EnvironmentManager* em;

    Path FindPath(int startTick, Coordinate start, Coordinate end, direction last, bool isCarrying);

    Path GetStupidPath(Coordinate start, Coordinate end);
    Path GetAstarPath(Coordinate start, Coordinate end, direction last, bool isCarrying);


};


#endif