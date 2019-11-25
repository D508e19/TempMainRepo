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
    Path pathFinder(Coordinate, direction, Coordinate);
private:

    std::list<Node*> openSet;
    Node* current;
    Node* endNode;
    std::pair<int, Node*> gScore;

    Path pathConstructer(Node* node, Path path);
    std::list<std::pair<Coordinate, Coordinate>> constructPath(Node*, std::list<std::pair<Coordinate, Coordinate>>);
};

aStar::aStar(){
    argos::LOG << "created ";
}


Path aStar::pathFinder(Coordinate start, direction d, Coordinate goal) {
    argos::LOG << "Hello1";

    Path pathList;
    Node* startNode = new Node(start,d);
    current = startNode;
    bool flag = true;

    do {
        argos::LOG << "Hello2 ";
        //Find the leaf with the lowest cost
        current = startNode->leastCost();
        //Check if the node is goal node
        if ((current->GetCoordinate().x == goal.x) && (current->GetCoordinate().y == goal.y)){
            return pathConstructer(current, pathList);
        }
        //Calculate neighbors of the node, should always be true, since current is always a leaf
        if (current->GetNeighbours().empty()){
            argos::LOG << "Hello3 ";
            current->calculateNeighbour();
        }
        argos::LOG << "Hello5 ";

        //Iterate through neighbors to find the best neighbor
        for(Node* node: current->GetNeighbours()){
            argos::LOG << "Hello7 ";
            //Set gScore
            node->SetgScore(node->GetParent()->GetgScore() + node->GetParentWeight());
            //Set fScore
            argos::LOG << "Hello8 ";

            node->SetfScore(node->GetgScore() + node->heuristic(goal));
        }
        //Reset flag
        flag = true;
    } while (!startNode->GetNeighbours().empty());
    return pathList;
}

Path aStar::pathConstructer(Node* node, Path path){
    std::list<std::pair<Coordinate, Coordinate>> wrong;
    Path right;
    std::pair<Coordinate, Coordinate> pair;

    wrong = constructPath(node, wrong);


    while (!wrong.empty()){
        pair = wrong.back();
        wrong.pop_back();
        right.AddWayPoint(pair.first, pair.second);
    }
    argos::LOG << "Hello4 ";

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
