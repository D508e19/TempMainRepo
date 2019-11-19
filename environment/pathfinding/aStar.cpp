//
// Created by Christopher krejler on 15/11/2019.
//

#include "aStar.h"


aStar::aStar(){
}


std::list<Coordinate> aStar::pathFinder(Coordinate start, direction d, Coordinate goal) {

    std::list<Coordinate> pathList;
    Node* startNode = new Node(start,d);
    startNode->gScore = 0;
    endNode = startNode;

    do {
        endNode = startNode->leastCost(startNode, goal);
        if ((endNode->coordinate.x == goal.x) && (endNode->coordinate.y == goal.y)){
            return constructPath(endNode, pathList);
        }

        if (endNode->neighbours.empty()){
            endNode->calculateNeighbour();
        }

        for(Node* node: endNode->neighbours){
            int tentative = endNode->gScore + node->parentWeight;

            if (tentative < node->gScore){
                endNode = node;
                node->gScore = tentative;
                node->fScore = node->gScore + node->heuristic(goal);
            }
        }
    } while ((startNode->neighbours.empty()));
}

std::list<Coordinate> aStar::constructPath(Node* node, std::list<Coordinate> list) {

    if(node->start){
        list.push_back(node->coordinate);
        return list;
    }
    else {
        list.push_back(node->coordinate);
        return constructPath(node->parent, list);
    }
}
