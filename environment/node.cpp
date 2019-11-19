#include "node.h"

//
// Created by Christopher krejler on 15/11/2019.
//

#include "node.h"


Node::Node() {
}

Node::Node(Coordinate c, enum direction d) {
    this->coordinate.x = c.x;
    this->coordinate.y = c.y;
    this->direction = d;
}
Node::Node(Coordinate c, enum direction d, Node* parent, int weight) {
    this->coordinate.x = c.x;
    this->coordinate.y = c.y;
    this->direction = d;
    this->direction = d;
    this->parent = parent;
    this->parentWeight = weight;
}


int Node::CostToRoot(class Node n){
    if (n.start){
        return 0;
    }
    else{
        return CostToRoot(*n.parent)+n.parentWeight;
    }
}


std::list<Node> Node::ReturnPath(class Node n, std::list<Node> path){
    if (n.start){
        path.push_back(n);
        return path;
    }
    else{
        path.push_back(n);
        return ReturnPath(reinterpret_cast<Node &&>(n.parent), path);
    }
}

int Node::heuristic(Coordinate goal){
    int gx = goal.x;
    int gy = goal.y;
    int nx = this->coordinate.x;
    int ny = this->coordinate.y;
    int h = 0;


    if ((this->direction == north || this->direction == south) && gx != nx){
        h += 3;
    } else if ((this->direction == west || this->direction == east) && gy != ny){
        h += 3;
    }
    if (gy < ny && this->direction != south){
        h += 3;
    }
    else if (gy > ny && this->direction != north){
        h+= 3;
    }
    else if (gx > nx && this->direction != east){
        h+= 3;
    }
    else if (gx < nx && this->direction != west){
        h += 3;
    }

    h+= abs(nx-gx);
    h+= abs(ny-gy);

    return h;
}


bool Node::calculateNeighbour() {
    if(this->direction == north){
        this->neighbours.push_back(new Node(*(new Coordinate(this->coordinate.x+1, this->coordinate.y)), north, this, 1));
        this->neighbours.push_back(new Node(this->coordinate, south, this, 3));
        this->neighbours.push_back(new Node(this->coordinate, east, this, 3));
        this->neighbours.push_back(new Node(this->coordinate, west, this, 3));
        this->neighbours.push_back(new Node(this->coordinate, north, this, 1));
    }

    if(this->direction == south){
        this->neighbours.push_back(new Node(this->coordinate, north, this, 3));
        this->neighbours.push_back(new Node(*(new Coordinate(this->coordinate.x, this->coordinate.y-1)), south, this, 1));
        this->neighbours.push_back(new Node(this->coordinate, east, this, 3));
        this->neighbours.push_back(new Node(this->coordinate, west, this, 3));
        this->neighbours.push_back(new Node(this->coordinate, south, this, 1));
    }
    if(this->direction == east){
        this->neighbours.push_back(new Node(this->coordinate, north, this, 3));
        this->neighbours.push_back(new Node(this->coordinate, south, this, 3));
        this->neighbours.push_back(new Node(*(new Coordinate(this->coordinate.x+1, this->coordinate.y)), east, this, 1));
        this->neighbours.push_back(new Node(this->coordinate, west, this, 3));
        this->neighbours.push_back(new Node(this->coordinate, east, this, 1));
    }
    if(this->direction == west){
        this->neighbours.push_back(new Node(this->coordinate, north, this, 3));
        this->neighbours.push_back(new Node(this->coordinate, south, this, 3));
        this->neighbours.push_back(new Node(this->coordinate, east, this, 3));
        this->neighbours.push_back(new Node(*(new Coordinate(this->coordinate.x, this->coordinate.y-1)), west, this, 1));
        this->neighbours.push_back(new Node(this->coordinate, west, this, 1));
    }
    return true;
}

Node* Node::leastCost(Node* node, Coordinate goal) {

    if(node->neighbours.empty()){
        return node;
    }

    else{
        Node* lowestCost;
        bool flag = true;
        for(Node* n: node->neighbours){
            if(flag){
                lowestCost = n->leastCost(n, goal);
                flag = false;
            } else if(lowestCost->fScore < n->leastCost(n, goal)->fScore){
                lowestCost = n;
            }
        }
    }
}
