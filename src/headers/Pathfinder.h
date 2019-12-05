#ifndef PATHFINDER_H
#define PATHFINDER_h

typedef std::list<std::pair<Coordinate, Coordinate>> simplePath;

class Pathfinder
{
private:
    int selectedAlgorithm;

    Node* currentNode;
    Path pathList;
    
    Path ReversePath(Node node, Path path);
    simplePath ConstructPath(Node, simplePath);
        
public:
    Pathfinder();
    ~Pathfinder();
   
    Path FindPath(Coordinate start, Coordinate end, direction last, bool isCarrying);

    Path GetStupidPath(Coordinate start, Coordinate end);
    Path GetAstarPath(Coordinate start, Coordinate end, direction last, bool isCarrying);


};


#endif