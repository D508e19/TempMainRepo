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
    bool CalculateNeighbour(int straightTime, int turnTime, int waitTime, EnvironmentManager* environmentManager);
    int CalculateHeuristic(Coordinate goal, int turnTime);
    static int CostToRoot(Node n);
    std::list<Node> ReturnPath(Node n, std::list<Node> path);
    int UpdateLeastCost();



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