#ifndef CUSTOM_NODE_H
#define CUSTOM_NODE_H

#include <list>

class Node
{
public:
    Node();
    Node(Coordinate, direction);
    Node(Coordinate, direction, Node*, int);
    Node(Coordinate, direction, Node*, int, bool);

    Node* LeastCost();
    bool CalculateNeighbour(int startTick, int straightTime, int turnTime, int waitTime, EnvironmentManager* environmentManager);
    int CalculateHeuristic(Coordinate goal, int turnTime, int straightTime);
    static int CostToRoot(Node n);
    std::list<Node> ReturnPath(Node n, std::list<Node> path);
    int UpdateLeastCost();
    Node* calculateWaitTime();

    bool addNeighborsNorth(int startTick, int straightTime, int turnTime, int waitTime, EnvironmentManager* environmentManager);
    bool addNeighborsSouth(int startTick, int straightTime, int turnTime, int waitTime, EnvironmentManager* environmentManager);
    bool addNeighborsEast(int startTick, int straightTime, int turnTime, int waitTime, EnvironmentManager* environmentManager);
    bool addNeighborsWest(int startTick, int straightTime, int turnTime, int waitTime, EnvironmentManager* environmentManager);





    bool isWait = false;
    bool deleteNode = false;
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