//
// Created by Christopher krejler on 15/11/2019.
//

#ifndef UNTITLED1_ASTAR_H
#define UNTITLED1_ASTAR_H


#include <map>
#include "../node.h"
#include "../../src/datatypes/Coordinate.h"
#include "../../src/datatypes/Path.h"
#include <queue>
#include <src/datatypes/direction>


class aStar {
public:
    aStar();
    Path pathFinder(Coordinate, direction, Coordinate);

    Node* current;
    Path pathList;
private:

    Path pathConstructer(Node node, Path path);
    std::list<std::pair<Coordinate, Coordinate>> constructPath(Node, std::list<std::pair<Coordinate, Coordinate>>);
};

aStar::aStar(){
    argos::LOG << "created ";
}

Path aStar::pathFinder(Coordinate start, direction d, Coordinate goal) {

    Node* startNode = new Node(start,d);
    current = startNode;
    int i = 0;

    do {
        //Find the leaf with the lowest cost
        current = (*startNode).leastCost();
        bool flag = true;

        argos::LOG << "Children after: " <<(*current).children.size() << std::endl;

        //Check if the node is goal node

        if (((*current).coordinate.x == goal.x) && ((*current).coordinate.y == goal.y)){
            argos::LOG << "\n IM FREEEEE ";

            return pathConstructer((*current), pathList);
        }
        //Calculate neighbors of the node, should always be true, since current is always a leaf
        if ((*current).children.empty()){

            (*current).calculateNeighbour();

            for (Node n : (*current).children){
                n.gScore = (*current).gScore + n.parentWeight;
                n.fScore = n.gScore + n.heuristic(goal);
                if(flag){
                    (*current).lowestCost = n.fScore;
                    flag = false;
                }
                else if(n.fScore < (*current).lowestCost){
                    (*current).lowestCost = n.fScore;
                }
            }
        }
        argos::LOG << "Children after after: " <<(*current).children.size() << std::endl;


        //Iterate through neighbors to find the best neighbor
        i++;
    } while (i<100);
    argos::LOG << "CRY!!! ";

    return pathList;
}

Path aStar::pathConstructer(Node node, Path path){
    std::list<std::pair<Coordinate, Coordinate>> wrong;
    Path right;
    std::pair<Coordinate, Coordinate> pair;

    wrong = constructPath(node, wrong);


    while (!wrong.empty()){
        pair = wrong.back();
        wrong.pop_back();
        right.AddWayPoint(pair.first, pair.second);
    }

    return right;
}


std::list<std::pair<Coordinate, Coordinate>> aStar::constructPath(Node node, std::list<std::pair<Coordinate, Coordinate>> path) {

    if(node.start){
        return path;
    }
    else {
        path.emplace_back(node.coordinate, (*node.parent).coordinate);

        return constructPath((*node.parent), path);
    }
}


#endif //UNTITLED1_ASTAR_H
