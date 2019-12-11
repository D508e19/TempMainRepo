#ifndef CUSTOM_NODE_CPP
#define CUSTOM_NODE_CPP

#include <src/headers/Node.h>

Node::Node(){}

Node::Node(Coordinate c, direction d) 
{
    coordinate = c;
    nodeDirection = d;
    lowestCost = 100000000;
    fScore = 100000000;
    gScore = 0;
    start = true;
    parentWeight = 0;
}

Node::Node(Coordinate c, direction d, Node* p, int weight)
{
    coordinate = c;
    nodeDirection = d;
    fScore = 1000000000;
    gScore = 1000000000;
    start = false;
    parent = p;
    parentWeight = weight;
}
Node::Node(Coordinate c, direction d, Node* p, int weight, bool _wait)
{
    coordinate = c;
    nodeDirection = d;
    fScore = 1000000000;
    gScore = 1000000000;
    start = false;
    parent = p;
    parentWeight = weight;
    isWait = _wait;
}

int Node::CostToRoot(Node node) //TODO: name change?
{
    if (node.start)
    {
        return 0;
    }
    else
    {
        return CostToRoot(*node.parent) + node.parentWeight;
    }
}

std::list<Node> Node::ReturnPath(Node node, std::list<Node> path) //TODO: name change
{
    if (node.start)
    {
        path.push_back(node);
        return path;
    }
    else
    {
        path.push_back(node);
        return ReturnPath(*node.parent, path);
    }
}

int Node::CalculateHeuristic(Coordinate goal, int turnTime, int straighTime)
{
    int gx = goal.x;
    int gy = goal.y;
    int nx = coordinate.x;
    int ny = coordinate.y;
    int h = 0;

    int deltaX = abs(nx-gx) * straighTime;;
    int deltaY = abs(ny-gy) * straighTime;

    if(gx == nx && gy == ny)
    {
        return h;
    }

    if(nodeDirection == north){
        if(gx != nx){ 
            h+= turnTime;
            if(gy < ny){ h+=turnTime;}
        }
        else if(gy < ny){ h+=2*turnTime; }
    }

    else if(nodeDirection == south){
        if(gx != nx){
            h+= turnTime;
            if(gy > ny){ h += turnTime; }
        }
        else if(gy > ny){ h+=2*turnTime; }
    }

    else if(nodeDirection == east){
        if(gy != ny){
            h+= turnTime;
            if(gx < nx){ h += turnTime; }
        }
        else if(gx < nx){ h+=2*turnTime; }
    }

    else if(nodeDirection == west){
        if(gy != ny){
            h+= turnTime;
            if(gx > nx){ h += turnTime; }
        }
        else if(gx > nx){ h += 2*turnTime; }
    }

    h+= deltaX;
    h+= deltaY;

    return h;
}

bool Node::CalculateNeighbour(int startTick, int straightTime, int turnTime, int waitTime, EnvironmentManager* environmentManager)
{
    switch (nodeDirection)
    {
        case north :
            return addNeighborsNorth(startTick, straightTime, turnTime, waitTime, environmentManager);

        case south :
            return addNeighborsSouth(startTick, straightTime, turnTime, waitTime, environmentManager);

        case east :
            return addNeighborsEast(startTick, straightTime, turnTime, waitTime, environmentManager);

        case west :
            return addNeighborsWest(startTick, straightTime, turnTime, waitTime, environmentManager);

        default:
            argos::LOGERR << "default. You shouldn't be here." << std::endl;
            return false;

    }
}

Node* Node::LeastCost() // TODO: change name to describe functionality
{
    if(children.empty())
    {
        if(deleteNode){
            return parent;
        }else{
            return this;
        }
    }
    else
    {
        Node* nodeWithLowestChild = (&children.front());

        for(Node& n : children) 
        {

            if ((*nodeWithLowestChild).lowestCost > n.lowestCost)
            {
                nodeWithLowestChild= (&n);
            }
        }
        return (*nodeWithLowestChild).LeastCost();
    }
}

int Node::UpdateLeastCost(){
    if(children.empty()){
        return this->fScore;
    }
    else{
        int ChildWithLowestFScore = children.front().UpdateLeastCost();
        for(Node& n : children){

            int temp = n.UpdateLeastCost();

            if(temp < ChildWithLowestFScore){
                ChildWithLowestFScore = temp;
            }
        }
        return ChildWithLowestFScore;
    }
}

Node *Node::calculateWaitTime() {
    if(parent->isWait){
        return parent->calculateWaitTime();
    }else {
        return this;
    }
}

bool Node::addNeighborsNorth(int startTick, int straightTime, int turnTime, int waitTime,
                             EnvironmentManager *environmentManager) {

    if(!environmentManager->IsReserved(Coordinate(coordinate.x, coordinate.y+1), startTick + gScore, startTick + gScore+straightTime) &&
    environmentManager->IsValidCoordinate(Coordinate(coordinate.x, coordinate.y+1))) {
        children.emplace_back(Node(Coordinate(coordinate.x, coordinate.y + 1), north, this, straightTime));
    }
//    else if(!environmentManager->IsReserved(Coordinate(coordinate.x, coordinate.y), startTick + gScore, startTick + ((gScore+waitTime)*10))) {
//        children.emplace_back(Coordinate(coordinate.x, coordinate.y), north, this, waitTime, true);
//    }
//    else{
//        return false;
//    }
    if(!environmentManager->IsReserved(coordinate, startTick + gScore, startTick + gScore+turnTime)) {

        children.emplace_back(Node(coordinate, south, this, turnTime));
    }
    if(!environmentManager->IsReserved(coordinate, startTick + gScore, startTick + gScore+turnTime)) {

        children.emplace_back(Node(coordinate, east, this, turnTime));
    }
    if(!environmentManager->IsReserved(coordinate, startTick + gScore, startTick + gScore+turnTime)) {

        children.emplace_back(Node(coordinate, west, this, turnTime));
    }
    return true;
}

bool Node::addNeighborsSouth(int startTick, int straightTime, int turnTime, int waitTime,
                             EnvironmentManager *environmentManager) {

    if(!environmentManager->IsReserved(coordinate, startTick + gScore, startTick + gScore+turnTime)) {

        children.emplace_back(Node(coordinate, north, this, turnTime));
    }
    if(!environmentManager->IsReserved(Coordinate(coordinate.x, coordinate.y-1), startTick + gScore, startTick + gScore+straightTime &&
            environmentManager->IsValidCoordinate(Coordinate(coordinate.x, coordinate.y-1)))) {
        children.emplace_back(Node(Coordinate(coordinate.x, coordinate.y - 1), south, this, straightTime));
    }
//    else if (!environmentManager->IsReserved(Coordinate(coordinate.x, coordinate.y), startTick + gScore, startTick + ((gScore+waitTime)*10))){
//        children.emplace_back(Coordinate(coordinate.x, coordinate.y), south, this, waitTime, true);
//    }
//    else {
//        return false;
//    }
    if(!environmentManager->IsReserved(coordinate, startTick + gScore, startTick + gScore+turnTime)) {
        children.emplace_back(Node(coordinate, east, this, turnTime));
    }
    if(!environmentManager->IsReserved(coordinate, startTick + gScore, startTick + gScore+turnTime)) {
        children.emplace_back(Node(coordinate, west, this, turnTime));
    }
    return true;
}

bool Node::addNeighborsEast(int startTick, int straightTime, int turnTime, int waitTime,
                            EnvironmentManager *environmentManager) {

    if(!environmentManager->IsReserved(coordinate, startTick + gScore, startTick + gScore+turnTime)) {
        children.emplace_back(Node(coordinate, north, this, turnTime));
    }
    if(!environmentManager->IsReserved(coordinate, startTick + gScore, startTick + gScore+turnTime)) {
        children.emplace_back(Node(coordinate, south, this, turnTime));
    }
    if(!environmentManager->IsReserved(Coordinate(coordinate.x + 1, coordinate.y), startTick + gScore, startTick + gScore+straightTime &&
            environmentManager->IsValidCoordinate(Coordinate(coordinate.x+1, coordinate.y)))) {

        children.emplace_back(Node(Coordinate(coordinate.x + 1, coordinate.y), east, this, straightTime));
    }
//    else if (!environmentManager->IsReserved(Coordinate(coordinate.x, coordinate.y), startTick + gScore, startTick + ((gScore+waitTime)*10))){
//        children.emplace_back(Coordinate(coordinate.x, coordinate.y), east, this, waitTime, true);
//    }
//    else {
//        return false;
//    }
    if(!environmentManager->IsReserved(coordinate, startTick + gScore, startTick + gScore+turnTime)) {
        children.emplace_back(Node(coordinate, west, this, turnTime));
    }
    return true;
}

bool Node::addNeighborsWest(int startTick, int straightTime, int turnTime, int waitTime,
                            EnvironmentManager *environmentManager) {

    if(!environmentManager->IsReserved(coordinate, startTick + gScore, startTick + gScore+turnTime)) {
        //Add North
        children.emplace_back(Node(coordinate, north, this, turnTime));
    }
    if(!environmentManager->IsReserved(coordinate, startTick + gScore, startTick + gScore+turnTime)) {
        //Add South
        children.emplace_back(Node(coordinate, south, this, turnTime));
    }
    if(!environmentManager->IsReserved(coordinate, startTick + gScore, startTick + gScore+turnTime)) {
        //Add East
        children.emplace_back(Node(coordinate, east, this, turnTime));
    }
    if(!environmentManager->IsReserved(Coordinate(coordinate.x - 1, coordinate.y), startTick + gScore, startTick + gScore+straightTime &&
            environmentManager->IsValidCoordinate(Coordinate(coordinate.x -1, coordinate.y)))) {
        //Add West
        children.emplace_back(Node(Coordinate(coordinate.x - 1, coordinate.y), west, this, straightTime));
    }
//        //If the coordinate is reserved, add wait
//    else if (!environmentManager->IsReserved(Coordinate(coordinate.x, coordinate.y), startTick + gScore, startTick + ((gScore+waitTime)*10))){
//        children.emplace_back(Coordinate(coordinate.x, coordinate.y), west, this, waitTime, true);
//    }
//        //If the current coordinate can't be waited on, delete node
//    else {
//        return false;
//    }
    return true;
}

#endif