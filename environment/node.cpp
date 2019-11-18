//
// Created by Christopher krejler on 12/11/2019.
//

#include "node.h"


int Node::CostToRoot(class Node n){
    if (n.start){
        return 0;
    }
    else{
        return CostToRoot(*n.parent)+n.parentWeight;
    }
}

//Vi mangler vel det vigtigste i form a distance til goal node?
int Node::heuristic(class Node n, class Node goal){
    int gx = goal.x;
    int gy = goal.y;
    int nx = n.x;
    int ny = n.y;
    int h = 0;


    if ((n.direction == n.North || n.direction == n.South) && gx != nx){
        h += 3;
    } else if ((n.direction == n.West || n.direction == n.East) && gy != ny){
        h += 3;
    }
    if (gy < ny && n.direction != n.South){
        h += 3;
    }
    else if (gy > ny && n.direction != n.North){
        h+= 3;
    }
    else if (gx > nx && n.direction != n.East){
        h+= 3;
    }
    else if (gx < nx && n.direction != n.West){
        h += 3;
    }

    return h;
}

Node::Node(int x, int y, Node::Direction d) {
    this->x = x;
    this->y = y;
    this->direction = d;
}

