//
// Created by Christopher krejler on 12/11/2019.
//

#include "node.h"

//
// Created by Christopher krejler on 15/11/2019.
//

#include "node.h"


Node::Node() {
}

Node::Node(int x, int y, Node::Direction d) {
    this->x = x;
    this->y = y;
    this->direction = d;
}
Node::Node(int x, int y, Node::Direction d, Node* parent, int weight) {
    this->x = x;
    this->y = y;
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


bool Node::calculateNeighbour() {
    if(this->direction == North){
        this->neighbours.push_back(new Node(this->x, this->y + 1, North, this, 1));
        this->neighbours.push_back(new Node(this->x, this->y, South, this, 3));
        this->neighbours.push_back(new Node(this->x, this->y, East, this, 3));
        this->neighbours.push_back(new Node(this->x, this->y, West, this, 3));
    }

    if(this->direction == South){
        this->neighbours.push_back(new Node(this->x, this->y, North, this, 3));
        this->neighbours.push_back(new Node(this->x, this->y-1, South, this, 1));
        this->neighbours.push_back(new Node(this->x, this->y, East, this, 3));
        this->neighbours.push_back(new Node(this->x, this->y, West, this, 3));
    }
    if(this->direction == East){
        this->neighbours.push_back(new Node(this->x, this->y, North, this, 3));
        this->neighbours.push_back(new Node(this->x, this->y, South, this, 3));
        this->neighbours.push_back(new Node(this->x, this->y+1, East, this, 1));
        this->neighbours.push_back(new Node(this->x, this->y, West, this, 3));
    }
    if(this->direction == West){
        this->neighbours.push_back(new Node(this->x, this->y, North, this, 3));
        this->neighbours.push_back(new Node(this->x, this->y, South, this, 3));
        this->neighbours.push_back(new Node(this->x, this->y, East, this, 3));
        this->neighbours.push_back(new Node(this->x, this->y-1, West, this, 1));
    }
    return true;
}

Node* Node::leastCost(Node* node, Node goal) {

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
