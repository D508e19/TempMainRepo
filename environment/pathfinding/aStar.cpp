//
// Created by Christopher krejler on 15/11/2019.
//

#include "aStar.h"


aStar::aStar(){
}


std::list<Node*> aStar::pathFinder(Coordinate start, direction d, Coordinate goal) {

    std::list<Node*> pathList;
    Node* startNode = new Node(start,d);
    endNode = startNode;
    openSet.push_back(startNode);


    while (!openSet.empty()){
        endNode = startNode->leastCost(startNode, goal);
        if ((endNode->coordinate.x == goal.x) && (endNode->coordinate.y == goal.y)){
            return constructPath(endNode, pathList);
        }

        openSet.remove(startNode);

        if(endNode->neighbours.empty()){
            if(!endNode->calculateNeighbour()){
                //cry
            }
        }
        for(Node* node: endNode->neighbours){
            int tentative = endNode->gScore + node->parentWeight;

            if (tentative < node->gScore){
                endNode = node;
                node->gScore = tentative;
                node->fScore = node->gScore + node->heuristic(goal);

                // if openset contains node
                if(true){
                    openSet.emplace_back(node);
                }
            }
        }
    }
}

std::list<Node*> aStar::constructPath(Node* node, std::list<Node*> list) {

    if(node->start){
        list.push_back(node);
        return list;
    }
    else {
        list.push_back(node);
        return constructPath(node->parent, list);
    }
}
