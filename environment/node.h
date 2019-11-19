//
// Created by Christopher krejler on 15/11/2019.
//

#ifndef UNTITLED1_NODE_H
#define UNTITLED1_NODE_H


#include <list>

class Node {
public:
    Node* parent;
    int parentWeight;
    int fScore;
    int gScore;
    int x;
    int y;
    bool start;
    enum Direction{North, South, East, West};
    Direction direction;

    std::list<Node*> neighbours;

    Node();
    Node(int, int, Node::Direction);
    Node(int, int, Node::Direction, Node*,int);
    int heuristic(Node goal);
    int CostToRoot(Node n);
    bool calculateNeighbour();


    std::list<Node> ReturnPath(Node n, std::list<Node> path);

    Node* leastCost(Node* base, Node goal);
};



#endif //UNTITLED1_NODE_H
