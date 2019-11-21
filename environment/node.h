//
// Created by Christopher krejler on 15/11/2019.
//

#ifndef UNTITLED1_NODE_H
#define UNTITLED1_NODE_H


#include <list>
#include "../src/datatypes/direction"
#include "../src/datatypes/Coordinate.h"


class Node {
public:
    Node* parent;
    int parentWeight = 0;
    int fScore = INT32_MAX;
    int gScore = INT32_MAX;
    bool start = false;
    bool open = true;
    Coordinate coordinate;
    direction direction;

    std::list<Node*> neighbours;

    Node();
    Node(Coordinate, enum direction);
    Node(Coordinate, enum direction, Node*, int);
    int heuristic(Coordinate goal);
    int CostToRoot(Node n);
    bool calculateNeighbour();


    std::list<Node> ReturnPath(Node n, std::list<Node> path);

    Node* leastCost(Node* base, Coordinate goal);
};



#endif //UNTITLED1_NODE_H
