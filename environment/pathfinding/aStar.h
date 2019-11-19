//
// Created by Christopher krejler on 15/11/2019.
//

#ifndef UNTITLED1_ASTAR_H
#define UNTITLED1_ASTAR_H


#include <map>
#include "../node.h"
#include "../../src/datatypes/Coordinate.h"
#include "../../src/datatypes/direction"

class aStar {
public:
    aStar();
    std::list<Node*> openSet;
    Node* current;
    Node* endNode;

    std::list<Node*> constructPath(Node*, std::list<Node*>);
    std::list<Node*> pathFinder(Coordinate, enum direction, Coordinate);
};


#endif //UNTITLED1_ASTAR_H
