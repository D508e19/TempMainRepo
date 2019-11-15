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

int Node::heuristic(Node goal){
    int gx = goal.x;
    int gy = goal.y;
    int nx = this->x;
    int ny = this->y;
    int h = 0;


    if ((this->direction == North || this->direction == South) && gx != nx){
        h += 3;
    } else if ((this->direction == West || this->direction == East) && gy != ny){
        h += 3;
    }
    if (gy < ny && this->direction != South){
        h += 3;
    }
    else if (gy > ny && this->direction != North){
        h+= 3;
    }
    else if (gx > nx && this->direction != East){
        h+= 3;
    }
    else if (gx < nx && this->direction != West){
        h += 3;
    }
    return h;
}

Node::Node(int x, int y, Node::Direction d) {
    this->x = x;
    this->y = y;
    this->direction = d;
}
Node::Node(int x, int y, Node::Direction d, Node parent, int weight) {
    this->x = x;
    this->y = y;
    this->direction = d;
    this->parent = &parent;
    this->parentWeight = weight;
}

bool Node::calculateNeighbour() {
    if(this->direction == North){
        this->neighbours.emplace_back(this->x, this->y+1, North, this, 1);
        this->neighbours.emplace_back(this->x, this->y, South, this, 3);
        this->neighbours.emplace_back(this->x, this->y, East, this, 3);
        this->neighbours.emplace_back(this->x, this->y, West, this, 3);
    }

    if(this->direction == South){
        this->neighbours.emplace_back(this->x, this->y, North, this, 3);
        this->neighbours.emplace_back(this->x, this->y-1, South, this, 1);
        this->neighbours.emplace_back(this->x, this->y, East, this, 3);
        this->neighbours.emplace_back(this->x, this->y, West, this, 3);
    }
    if(this->direction == East){
        this->neighbours.emplace_back(this->x, this->y, North, this, 3);
        this->neighbours.emplace_back(this->x, this->y, South, this, 3);
        this->neighbours.emplace_back(this->x, this->y+1, East, this, 1);
        this->neighbours.emplace_back(this->x, this->y, West, this, 3);
    }
    if(this->direction == West){
        this->neighbours.emplace_back(this->x, this->y, North, this, 3);
        this->neighbours.emplace_back(this->x, this->y, South, this, 3);
        this->neighbours.emplace_back(this->x, this->y, East, this, 3);
        this->neighbours.emplace_back(this->x, this->y-1, West, this, 1);
    }
    return true;
}

