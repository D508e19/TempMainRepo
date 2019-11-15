//
// Created by Christopher krejler on 14/11/2019.
//

#include "aStar.h"

int aStar::weight(Node, Node) {
    return 0;
}

aStar::aStar(const Node& goal, Node startNode){
    gScore[*start] = 0;
    fScore[*start] = start->heuristic(goal);
    Node endNode = startNode;
    openSet.emplace_back(start);

    while (!openSet.empty()){
        current = (*min_element(fScore.begin(), fScore.end
                (), &aStar::pairCompare )).first;
        if ((current.x == goal.x) && (current.y == goal.y)){
            //Success madafacka
        }

        openSet.remove(current);

        if(current.neighbours.empty()){
            if(!current.calculateNeighbour()){
                //cry
            }
        }
        for(Node node: current.neighbours){
            int tentative = gScore[current] + node.parentWeight;

            if (gScore.count(node) > 0  && tentative < gScore[node]){
                endNode = node;
                gScore[node] = tentative;
                fScore[node] = gScore[node] + node.heuristic(goal);
                if((std::find(openSet.begin(), openSet.end(), node) != openSet.end())){
                    openSet.emplace_back(node);
                }
            }
        }


    }
}

bool aStar::pairCompare(std::pair<Node, int> i, std::pair<Node, int> j) {
    return i.second < j.second;
}


