//
// Created by Christopher krejler on 15/11/2019.
//

#ifndef UNTITLED1_NODE_H
#define UNTITLED1_NODE_H


#include <list>
#include <src/datatypes/direction>
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
    direction GetDir();

    std::list<Node> GetNeighbours();

    Node leastCost(Node base);
    bool calculateNeighbour();
    int heuristic(Coordinate goal);
    static int CostToRoot(Node n);
    static std::list<Node> ReturnPath(Node n, std::list<Node> path);

    Node* parent;
    int parentWeight;
    int fScore;
    int gScore;
    bool start;
    bool open;
    Coordinate coordinate;
    direction Dir;

    std::list<Node> neighbours;
};


Node::Node(Coordinate c, direction d) {
    this->coordinate.x = c.x;
    this->coordinate.y = c.y;
    this->Dir = d;
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
    this->Dir = d;
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

    int deltaX = abs(nx-gx);;
    int deltaY = abs(ny-gy);



    if(gx == nx && gy == ny){
        return h;
    }
    if ((this->Dir == north || this->Dir == south) && gx != nx){
        h += 3;
    }
    else if ((this->Dir == west || this->Dir == east) && gy != ny){
        h += 3;
    }
    if (gy > ny && this->Dir == south){
        h += 3;
    }
    if (gy < ny && this->Dir == north){
        h+= 3;
    }
    else if (gx < nx && this->Dir == east){
        h+= 3;
    }
    else if (gx > nx && this->Dir == west){
        h += 3;
    }

    h+= deltaX;
    h+= deltaY;



    argos::LOG << h;
    argos::LOG << "\n";


    return h;
}


bool Node::calculateNeighbour() {

    switch (this->Dir)
    {
        case north :
            this->neighbours.push_back((*(new Node(*(new Coordinate(this->coordinate.x+1, this->coordinate.y)), north, this, 3))));
            this->neighbours.push_back((*(new Node(this->coordinate, south, this, 3))));
            this->neighbours.push_back((*(new Node(this->coordinate, east, this, 3))));
            this->neighbours.push_back((*(new Node(this->coordinate, west, this, 3))));
            //this->neighbours.push_back(new Node(this->coordinate, north, this, 1));
            break;
        case south :

            this->neighbours.push_back((*(new Node(this->coordinate, north, this, 3))));
            this->neighbours.push_back((*(new Node(*(new Coordinate(this->coordinate.x, this->coordinate.y-1)), south, this, 3))));
            this->neighbours.push_back((*(new Node(this->coordinate, east, this, 3))));
            this->neighbours.push_back((*(new Node(this->coordinate, west, this, 3))));
            //this->neighbours.push_back(new Node(this->coordinate, south, this, 1));

            break;
        case east :

            this->neighbours.push_back((*(new Node(this->coordinate, north, this, 3))));
            this->neighbours.push_back((*(new Node(this->coordinate, south, this, 3))));
            this->neighbours.push_back((*(new Node(*(new Coordinate(this->coordinate.x+1, this->coordinate.y)), east, this, 3))));
            this->neighbours.push_back((*(new Node(this->coordinate, west, this, 3))));
            //this->neighbours.push_back(new Node(this->coordinate, east, this, 1));

            break;
        case west :

            this->neighbours.push_back((*(new Node(this->coordinate, north, this, 3))));
            this->neighbours.push_back((*(new Node(this->coordinate, south, this, 3))));
            this->neighbours.push_back((*(new Node(this->coordinate, east, this, 3))));
            this->neighbours.push_back((*(new Node(*(new Coordinate(this->coordinate.x, this->coordinate.y-1)), west, this, 3))));
            //this->neighbours.push_back(new Node(this->coordinate, west, this, 1));

            break;
        default:
            break;
    }


    return true;
}

Node Node::leastCost(Node node) {

    Node lowestCost;
    bool flag = true;

    argos::LOG << node.neighbours.size();

    if(node.neighbours.empty()){
        argos::LOG << "Leaf ";

        return (*this);
    }
    else{
        argos::LOG << "LeastCost else ";
        for(Node n: node.neighbours){
            if(flag){
                lowestCost = n.leastCost(n);
                flag = false;
            } else if(lowestCost.fScore < n.leastCost(n).fScore){
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

direction Node::GetDir() {
    return this->Dir;
}

std::list<Node> Node::GetNeighbours() {
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

Node::Node() {

}

#endif //UNTITLED1_NODE_H
