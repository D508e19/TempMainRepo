//
// Created by Christopher krejler on 12/11/2019.
//

#ifndef KBOT_NODE_H
#define KBOT_NODE_H

#include <list>

class Node;

class Node {

public:
    Node* parent;
    int parentWeight;
    int x;
    int y;
    bool start;
    enum Direction{North, South, East, West};
    Direction direction;

    std::list<Node> neighbours;

    Node(int, int, Node::Direction);
    Node(int, int, Node::Direction, Node,int);
    int heuristic(Node);
    int CostToRoot(Node n);
    bool calculateNeighbour();
};


#endif //KBOT_NODE_H
