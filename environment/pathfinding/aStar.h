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
private:

    Node current;

    Path pathConstructer(Node node, Path path);
    std::list<std::pair<Coordinate, Coordinate>> constructPath(Node, std::list<std::pair<Coordinate, Coordinate>>);
};

aStar::aStar(){
    argos::LOG << "created ";
}

Path aStar::pathFinder(Coordinate start, direction d, Coordinate goal) {


    argos::LOG << "\n";
    argos::LOG << start.x;
    argos::LOG << "\n";
    argos::LOG << start.y;
    argos::LOG << "\n";


    Path pathList;
    Node startNode = (*new Node(start,d));
    current = startNode;
    int i = 0;
    do {
        //Find the leaf with the lowest cost

        current = startNode.leastCost(startNode);

        if (current.GetDir() == north){
            argos::LOG << "\n  North ";

        }
        else if (current.GetDir() == south){
            argos::LOG << "\n  South ";

        }
        else if (current.GetDir() == east){
            argos::LOG << "\n  East ";

        }
        else if (current.GetDir() == west){
            argos::LOG << "\n  West ";

        }


        //Check if the node is goal node

        if ((current.GetCoordinate().x == goal.x) && (current.GetCoordinate().y == goal.y)){
            return pathConstructer(current, pathList);
        }
        //Calculate neighbors of the node, should always be true, since current is always a leaf
        if (current.GetNeighbours().empty()){
            current.calculateNeighbour();
        }

        //Iterate through neighbors to find the best neighbor
        argos::LOG << "\n  ---Neighbours size: ";

        argos::LOG << current.neighbours.size();

        for(Node node: current.GetNeighbours()){
            //Set gScore
            node.SetgScore((*node.GetParent()).GetgScore() + node.GetParentWeight());
            //Set fScore
            node.SetfScore(node.GetgScore() + node.heuristic(goal));
        }
        //Reset flag
        i++;
    } while (i<1000);
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
    argos::LOG << "Hello4 ";

    return right;
}


std::list<std::pair<Coordinate, Coordinate>> aStar::constructPath(Node node, std::list<std::pair<Coordinate, Coordinate>> path) {

    if(node.Getstart()){
        return path;
    }
    else {
        path.emplace_back(node.GetCoordinate(), (*node.GetParent()).GetCoordinate());

        return constructPath((*node.GetParent()), path);
    }
}


#endif //UNTITLED1_ASTAR_H
