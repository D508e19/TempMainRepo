//
// Created by Christopher krejler on 15/11/2019.
//

#ifndef UNTITLED1_ASTAR_H
#define UNTITLED1_ASTAR_H


#include <map>
#include "../node.h"
#include "../../src/datatypes/Coordinate.h"
#include "../../src/datatypes/direction"
#include "../../src/datatypes/Path.h"
#include <queue>


class aStar {
public:
    aStar();
    Path pathFinder(const Coordinate&, enum direction, const Coordinate&);
private:

    std::list<Node*> openSet;
    Node* current;
    Node* endNode;
    std::pair<int, Node*> gScore;

    static Path pathConstructer(Node* node, const Path& path);
    static std::list<std::pair<Coordinate, Coordinate>> constructPath(Node*, std::list<std::pair<Coordinate, Coordinate>>);
};

aStar::aStar()= default;


Path aStar::pathFinder(const Coordinate& start, direction d, const Coordinate& goal) {

    Path pathList;
    Node* startNode = new Node(start,d);
    startNode->SetgScore(0);
    current = startNode;
    bool flag = true;

    do {
        //Find the leaf with the lowest cost
        current = startNode->leastCost(goal);
        //Check if the node is goal node
        if ((current->GetCoordinate().x == goal.x) && (current->GetCoordinate().y == goal.y)){
            return pathConstructer(current, pathList);
        }
        //Calculate neighbors of the node, should always be true, since current is always a leaf
        if (current->GetNeighbours().empty()){
            current->calculateNeighbour();
        }
        //Iterate through neighbors to find the best neighbor
        for(Node* node: current->GetNeighbours()){
            //Set gScore
            node->SetgScore(node->GetParent()->GetgScore() + node->GetParentWeight());
            //Set fScore
            node->SetfScore(node->GetgScore() + node->heuristic(goal));
//            //Check if it's the first neighbor, if not, check if it's the best neighbor
//            if (flag){
//                current = node;
//                flag = false;
//            }
//            else if(current->fScore > node->fScore){
//                current = node;
//            }
        }
        //Reset flag
        flag = true;
    } while (!(startNode->GetNeighbours().empty()));
    return pathList;
}

Path aStar::pathConstructer(Node* node, const Path& path){
    std::list<std::pair<Coordinate, Coordinate>> wrong;
    Path right;
    std::pair<Coordinate, Coordinate> pair;

    wrong = constructPath(node, wrong);

    while (!wrong.empty()){
        pair = wrong.front();
        wrong.pop_front();
        right.AddWayPoint(pair.first, pair.second);
    }
    return right;
}


std::list<std::pair<Coordinate, Coordinate>> aStar::constructPath(Node* node, std::list<std::pair<Coordinate, Coordinate>> path) {

    if(node->Getstart()){
        return path;
    }
    else {
        path.emplace_back(node->GetCoordinate(), node->GetParent()->GetCoordinate());
        return constructPath(node->GetParent(), path);
    }
}


#endif //UNTITLED1_ASTAR_H
