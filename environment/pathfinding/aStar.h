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
    std::pair<int, Node*> gScore;

    Path pathConstructer(Node* node, Path path);
    std::list<std::pair<Coordinate, Coordinate>> constructPath(Node*, std::list<std::pair<Coordinate, Coordinate>>);
    Path pathFinder(Coordinate, enum direction, Coordinate);
};


#endif //UNTITLED1_ASTAR_H
