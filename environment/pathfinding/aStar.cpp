//
// Created by Christopher krejler on 15/11/2019.
//

#include <queue>
#include <src/datatypes/Path.h>
#include "aStar.h"


aStar::aStar(){
}


Path aStar::pathFinder(Coordinate start, direction d, Coordinate goal) {

    Path pathList;
    Node* startNode = new Node(start,d);
    startNode->gScore = 0;
    current = startNode;
    bool flag = true;

    do {
        //Find the leaf with the lowest cost
        current = startNode->leastCost(startNode, goal);
        //Check if the node is goal node
        if ((current->coordinate.x == goal.x) && (current->coordinate.y == goal.y)){
            return pathConstructer(current, pathList);
        }
        //Calculate neighbors of the node, should always be true, since current is always a leaf
        if (current->neighbours.empty()){
            current->calculateNeighbour();
        }
        //Iterate through neighbors to find the best neighbor
        for(Node* node: current->neighbours){
            //Set gScore
            node->gScore = node->parent->gScore + node->parentWeight;
            //Set fScore
            node->fScore = node->gScore + node->heuristic(goal);
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
    } while (!(startNode->neighbours.empty()));
}

Path aStar::pathConstructer(Node* node, Path path){
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

    if(node->start){
        return path;
    }
    else {
        path.push_back(std::pair<Coordinate, Coordinate>(node->coordinate, node->parent->coordinate));
        return constructPath(node->parent, path);
    }
}
