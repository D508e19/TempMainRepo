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
    aStar(const Node& goal, Node start);

    std::list<Node> openSet;
    std::map<Node, int> gScore;
    std::map<Node, int> fScore;
    Node* start;
    Node current = *start;
    int goalX;
    int goalY;
    int weight(Node, Node);

    bool pairCompare(std::pair<Node, int> i, std::pair<Node, int> j);
};


#endif //KBOT_ASTAR_H
