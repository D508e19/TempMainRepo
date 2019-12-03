#ifndef CUSTOM_NODE_H
#define CUSTOM_NODE_H

#include <list>

class Node
{
public:
    Node();
    Node(Coordinate, direction);
    Node(Coordinate, direction, Node*, int);

    Node* LeastCost();
    void CalculateNeighbour();
    int CalculateHeuristic(Coordinate goal);
    static int CostToRoot(Node n);
    std::list<Node> ReturnPath(Node n, std::list<Node> path);
    Node GetNode(std::list<Node>, int);

    Node* parent;
    int lowestCost;
    int parentWeight;
    int fScore;
    int gScore;
    bool start;
    Coordinate coordinate;
    direction nodeDirection;
    std::list<Node> children;
};


#endif