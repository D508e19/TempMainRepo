//
// Created by Christopher krejler on 15/11/2019.
//

#ifndef UNTITLED1_NODE_H
#define UNTITLED1_NODE_H


#include <list>
#include "../src/datatypes/direction"
#include "../src/datatypes/Coordinate.h"


class Node {
public:
    Node();
    Node(Coordinate, direction);
    Node(Coordinate, direction, Node*, int);

    Node* GetParent();
    int GetParentWeight();
    int GetfScore();
    void SetfScore(int score);
    int GetgScore();
    void SetgScore(int);
    bool Getstart();
    void Setstart(bool);
    bool Getopen();
    Coordinate GetCoordinate();
    direction GetDirection();

    std::list<Node*> GetNeighbours();

    Node* leastCost();
    bool calculateNeighbour();
    int heuristic(Coordinate goal);
    static int CostToRoot(Node n);
    static std::list<Node> ReturnPath(Node n, std::list<Node> path);

private:
    Node* parent;
    int parentWeight;
    int fScore;
    int gScore;
    bool start;
    bool open;
    Coordinate coordinate;
    direction Direction;

    std::list<Node*> neighbours;
};

Node::Node() {
    this->parentWeight = 0;
    this->fScore = 1000000000;
    this->gScore = 1000000000;
    this->start = false;
    this->open = true;
}

Node::Node(Coordinate c, direction d) {
    this->coordinate.x = c.x;
    this->coordinate.y = c.y;
    this->Direction = d;
    this->parentWeight = 0;
    this->fScore = 0;
    this->gScore = 0;
    this->start = true;
    this->open = true;
}
Node::Node(Coordinate c, direction d, Node* parent, int weight) {
    this->fScore = 1000000000;
    this->gScore = 1000000000;
    this->start = false;
    this->open = true;
    this->Direction = d;
    this->coordinate.x = c.x;
    this->coordinate.y = c.y;
    this->parent = parent;
    this->parentWeight = weight;
}


int Node::CostToRoot(Node n){
    if (n.start){
        return 0;
    }
    else{
        return CostToRoot(*n.parent)+n.parentWeight;
    }
}


std::list<Node> Node::ReturnPath(Node n, std::list<Node> path){
    if (n.start){
        argos::LOG << "Hello11 ";
        path.push_back(n);
        return path;
    }
    else{
        path.push_back(n);
        return ReturnPath(*n.parent, path);
    }
}

int Node::heuristic(Coordinate goal){
    int gx = goal.x;
    int gy = goal.y;
    int nx = this->coordinate.x;
    int ny = this->coordinate.y;
    int h = 0;


    if ((this->Direction == north || this->Direction == south) && gx != nx){
        h += 3;
    } else if ((this->Direction == west || this->Direction == east) && gy != ny){
        h += 3;
    }
    if (gy < ny && this->Direction != south){
        h += 3;
    }
    else if (gy > ny && this->Direction != north){
        h+= 3;
    }
    else if (gx > nx && this->Direction != east){
        h+= 3;
    }
    else if (gx < nx && this->Direction != west){
        h += 3;
    }

    h+= abs(nx-gx);
    h+= abs(ny-gy);

    return h;
}


bool Node::calculateNeighbour() {
    switch (this->Direction)
    {
        case north :
            argos::LOG << "Hello6 ";
            this->neighbours.push_back(new Node(*(new Coordinate(this->coordinate.x+1, this->coordinate.y)), north, this, 1));
            argos::LOG << "Hello6 ";
            this->neighbours.push_back(new Node(this->coordinate, south, this, 3));
            argos::LOG << "Hello6 ";
            this->neighbours.push_back(new Node(this->coordinate, east, this, 3));
            argos::LOG << "Hello6 ";
            this->neighbours.push_back(new Node(this->coordinate, west, this, 3));
            argos::LOG << "Hello6 ";
            //this->neighbours.push_back(new Node(this->coordinate, north, this, 1));
            break;
        case south :
            argos::LOG << "Hello6 ";
            this->neighbours.push_back(new Node(this->coordinate, north, this, 3));
            argos::LOG << "Hello6 ";
            this->neighbours.push_back(new Node(*(new Coordinate(this->coordinate.x, this->coordinate.y-1)), south, this, 1));
            argos::LOG << "Hello6 ";
            this->neighbours.push_back(new Node(this->coordinate, east, this, 3));
            argos::LOG << "Hello6 ";
            this->neighbours.push_back(new Node(this->coordinate, west, this, 3));
            argos::LOG << "Hello6 ";
            //this->neighbours.push_back(new Node(this->coordinate, south, this, 1));
            break;
        case east :
            argos::LOG << "Hello6 ";
            this->neighbours.push_back(new Node(this->coordinate, north, this, 3));
            argos::LOG << "Hello6 ";
            this->neighbours.push_back(new Node(this->coordinate, south, this, 3));
            argos::LOG << "Hello6 ";
            this->neighbours.push_back(new Node(*(new Coordinate(this->coordinate.x+1, this->coordinate.y)), east, this, 1));
            argos::LOG << "Hello6 ";
            this->neighbours.push_back(new Node(this->coordinate, west, this, 3));
            argos::LOG << "Hello6 ";
            //this->neighbours.push_back(new Node(this->coordinate, east, this, 1));
            break;
        case west :
            argos::LOG << "Hello6 ";
            this->neighbours.push_back(new Node(this->coordinate, north, this, 3));
            argos::LOG << "Hello6 ";
            this->neighbours.push_back(new Node(this->coordinate, south, this, 3));
            argos::LOG << "Hello6 ";
            this->neighbours.push_back(new Node(this->coordinate, east, this, 3));
            argos::LOG << "Hello6 ";
            this->neighbours.push_back(new Node(*(new Coordinate(this->coordinate.x, this->coordinate.y-1)), west, this, 1));
            argos::LOG << "Hello6 ";
            //this->neighbours.push_back(new Node(this->coordinate, west, this, 1));
            break;
        default:
            argos::LOG << "Hello6 ";
            break;
    }

    argos::LOG << "Hello6 ";
    return true;
}

Node* Node::leastCost() {

    Node* lowestCost;
    bool flag = true;

    if(this->neighbours.empty()){
        return this;
    }

    else{
        argos::LOG << "LeastCost else ";
        for(Node* n: this->neighbours){
            if(flag){
                lowestCost = n->leastCost();
                flag = false;
            } else if(lowestCost->fScore < (n->leastCost())->fScore){
                lowestCost = n;
            }
        }
        argos::LOG << "returning least cost ";
        return lowestCost;
    }
}

Node *Node::GetParent() {
    return this->parent;
}

int Node::GetParentWeight() {
    return this->parentWeight;
}

int Node::GetfScore() {
    return this->fScore;
}

int Node::GetgScore() {
    return this->gScore;
}

bool Node::Getstart() {
    return this->start;
}

bool Node::Getopen() {
    return this->open;
}

Coordinate Node::GetCoordinate() {
    return this->coordinate;
}

direction Node::GetDirection() {
    return this->Direction;
}

std::list<Node *> Node::GetNeighbours() {
    return this->neighbours;
}

void Node::SetgScore(int score) {
    this->gScore = score;
}

void Node::SetfScore(int score) {
    this->fScore = score;
}

void Node::Setstart(bool start) {
    this->start = start;
}

#endif //UNTITLED1_NODE_H
