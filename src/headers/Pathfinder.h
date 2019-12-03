#ifndef PATHFINDER_H
#define PATHFINDER_h

typedef std::list<std::pair<Coordinate, Coordinate>> simplePath;

class Pathfinder
{
private:
    int selectedAlgorithm;

    Node* currentNode;
    Path pathList;
    
    Path PathConstructer(Node node, Path path);
    simplePath ConstructPath(Node, simplePath);
        
public:
    Pathfinder();
    ~Pathfinder();
   
    Path FindPath(Coordinate start, Coordinate end, direction last);

    Path GetStupidPath(Coordinate start, Coordinate end);
    Path GetAstarPath(Coordinate start, Coordinate end, direction last);

};


#endif