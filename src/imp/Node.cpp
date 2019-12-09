#ifndef CUSTOM_NODE_CPP
#define CUSTOM_NODE_CPP

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

int Node::CalculateHeuristic(Coordinate goal, int turnTime)
{
    int gx = goal.x;
    int gy = goal.y;
    int nx = coordinate.x;
    int ny = coordinate.y;
    int h = 0;

    int deltaX = abs(nx-gx);;
    int deltaY = abs(ny-gy);

    if(gx == nx && gy == ny)
    {
        return h;
    }

    if(nodeDirection == north){
        if(gx != nx){ 
            h+= turnTime;
            if(gy < ny){ h+=turnTime*3; }
            else {h+=turnTime;}
        }
        else if(gy < ny){ h+=2*turnTime; }
    }

    else if(nodeDirection == south){
        if(gx != nx){
            h+= turnTime;
            if(gy > ny){ h += turnTime*3; }
            else {h+=turnTime;}
        }
        else if(gy > ny){ h+=2*turnTime; }
    }

    else if(nodeDirection == east){
        if(gy != ny){
            h+= turnTime;
            if(gx < nx){ h += turnTime*3; }
            else {h+=turnTime;}
        }
        else if(gx < nx){ h+=2*turnTime; }
    }
    else if(nodeDirection == west){
        if(gy != ny){
            h+= turnTime;
            if(gx > nx){ h += turnTime*3; }
            else {h+=turnTime;}
        }
        else if(gx > nx){ h += 2*turnTime; }
    }

    h+= deltaX;
    h+= deltaY;

    return h;
}

bool Node::CalculateNeighbour(int straightTime, int turnTime, int waitTime, EnvironmentManager* environmentManager)
{

    switch (nodeDirection)
    {
        case north :
            if(!(*environmentManager).IsReserved(Coordinate(coordinate.x, coordinate.y+1), gScore, gScore+straightTime)) {
                children.emplace_back(Node(Coordinate(coordinate.x, coordinate.y + 1), north, this, straightTime));
            }
            else if(!(*environmentManager).IsReserved(Coordinate(coordinate.x, coordinate.y), gScore, gScore+waitTime)) {
                children.emplace_back(Coordinate(coordinate.x, coordinate.y), north, this, waitTime);
            }
            else{
                return false;
            }
            if(!(*environmentManager).IsReserved(coordinate, gScore, gScore+turnTime)) {

                children.emplace_back(Node(coordinate, south, this, turnTime));
            }
            if(!(*environmentManager).IsReserved(coordinate, gScore, gScore+turnTime)) {

                children.emplace_back(Node(coordinate, east, this, turnTime));
            }
            if(!(*environmentManager).IsReserved(coordinate, gScore, gScore+turnTime)) {

                children.emplace_back(Node(coordinate, west, this, turnTime));
            }
            return true;
        case south :
            if(!(*environmentManager).IsReserved(coordinate, gScore, gScore+turnTime)) {

                children.emplace_back(Node(coordinate, north, this, turnTime));
            }
            else if (!(*environmentManager).IsReserved(Coordinate(coordinate.x, coordinate.y), gScore, gScore+waitTime)){
                children.emplace_back(Coordinate(coordinate.x, coordinate.y), north, this, waitTime);
            }
            else {
                return false;
            }
            if(!(*environmentManager).IsReserved(Coordinate(coordinate.x, coordinate.y-1), gScore, gScore+straightTime)) {

                if(!coordinate.y-1 < 0) {
                    children.emplace_back(Node(Coordinate(coordinate.x, coordinate.y - 1), south, this, straightTime));
                }
            }
            if(!(*environmentManager).IsReserved(coordinate, gScore, gScore+turnTime)) {


                children.emplace_back(Node(coordinate, east, this, turnTime));
            }
            if(!(*environmentManager).IsReserved(coordinate, gScore, gScore+turnTime)) {


                children.emplace_back(Node(coordinate, west, this, turnTime));
            }
            return true;
        case east :
            if(!(*environmentManager).IsReserved(coordinate, gScore, gScore+turnTime)) {

                children.emplace_back(Node(coordinate, north, this, turnTime));
            }
            else if (!(*environmentManager).IsReserved(Coordinate(coordinate.x, coordinate.y), gScore, gScore+waitTime)){
                children.emplace_back(Coordinate(coordinate.x, coordinate.y), north, this, waitTime);
            }
            else {
                return false;
            }
            if(!(*environmentManager).IsReserved(coordinate, gScore, gScore+turnTime)) {


                children.emplace_back(Node(coordinate, south, this, turnTime));
            }
            if(!(*environmentManager).IsReserved(Coordinate(coordinate.x + 1, coordinate.y), gScore, gScore+straightTime)) {


                children.emplace_back(Node(Coordinate(coordinate.x + 1, coordinate.y), east, this, straightTime));
            }
            if(!(*environmentManager).IsReserved(coordinate, gScore, gScore+turnTime)) {


                children.emplace_back(Node(coordinate, west, this, turnTime));
            }
            return true;
        case west :
            if(!(*environmentManager).IsReserved(coordinate, gScore, gScore+turnTime)) {

                children.emplace_back(Node(coordinate, north, this, turnTime));
            }
            else if (!(*environmentManager).IsReserved(Coordinate(coordinate.x, coordinate.y), gScore, gScore+waitTime)){
                children.emplace_back(Coordinate(coordinate.x, coordinate.y), north, this, waitTime);
            }
            else {
                return false;
            }
            if(!(*environmentManager).IsReserved(coordinate, gScore, gScore+turnTime)) {


                children.emplace_back(Node(coordinate, south, this, turnTime));
            }
            if(!(*environmentManager).IsReserved(coordinate, gScore, gScore+turnTime)) {


                children.emplace_back(Node(coordinate, east, this, turnTime));
            }
            if(!(*environmentManager).IsReserved(Coordinate(coordinate.x - 1, coordinate.y), gScore, gScore+straightTime)) {

                if(coordinate.x - 1 < 0) {
                    children.emplace_back(Node(Coordinate(coordinate.x - 1, coordinate.y), west, this, straightTime));
                }
            }
            return true;
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

#endif