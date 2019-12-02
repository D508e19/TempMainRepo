#ifndef CUSTOM_NODE_H
#define CUSTOM_NODE_H

#include <list>
//#include "src/datatypes/direction.h"
//#include "src/headers/Coordinate.h"

class Node {
public:
    Node();
    Node(Coordinate, direction);
    Node(Coordinate, direction, Node*, int);

    Node* leastCost();
    void calculateNeighbour();
    int heuristic(Coordinate goal);
    static int CostToRoot(Node n);
    std::list<Node> ReturnPath(Node n, std::list<Node> path);
    Node getNode(std::list<Node>, int);

    Node* parent;
    int lowestCost;
    int parentWeight;
    int fScore;
    int gScore;
    bool start;
    Coordinate coordinate;
    direction Dir;
    std::list<Node> children;
};


#endif