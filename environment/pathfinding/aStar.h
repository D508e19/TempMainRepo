//
// Created by Christopher krejler on 14/11/2019.
//

#ifndef KBOT_ASTAR_H
#define KBOT_ASTAR_H


#include <environment/node.h>
#include <list>
#include <map>

class aStar {
public:
    aStar(int x, int y, Node start);

private:
    std::list<Node> openSet;
    std::list<Node> cheapestPath;
    std::map<Node, int> fScore;
    Node start;
    Node current = start;
    int goalX;
    int goalY;
    int weight(Node, Node);
};


#endif //KBOT_ASTAR_H
