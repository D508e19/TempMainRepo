//
// Created by Christopher krejler on 15/11/2019.
//

#ifndef UNTITLED1_ASTAR_H
#define UNTITLED1_ASTAR_H


#include <map>
#include "../node.h"

class aStar {
public:
    aStar();
    std::list<Node*> openSet;
    Node* current;
    Node* endNode;
    std::list<Node*> pathList;

    std::list<Node*> constructPath(Node*, std::list<Node*>);
    std::list<Node*> pathFinder(Node* h, Node t);
};


#endif //UNTITLED1_ASTAR_H
