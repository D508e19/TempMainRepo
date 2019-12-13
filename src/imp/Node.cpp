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

int Node::CostToRoot(Node node)
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

std::list<Node> Node::ReturnPath(Node node, std::list<Node> path)
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

int Node::CalculateHeuristic(Coordinate goal)
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
            h+= 3;
            if(gy < ny){ h+=3; }
        }
        else if(gy < ny){ h+=6; }
    }

    else if(nodeDirection == south){
        if(gx != nx){
            h+= 3;
            if(gy > ny){ h += 3; }
        }
        else if(gy > ny){ h+=6; }
    }

    else if(nodeDirection == east){
        if(gy != ny){
            h+= 3;
            if(gx < nx){ h += 3; }
        }
        else if(gx < nx){ h+=6; }
    }
    else if(nodeDirection == west){
        if(gy != ny){
            h+= 3;
            if(gx > nx){ h += 3; }
        }
        else if(gx > nx){ h += 6; }
    }

    h+= deltaX;
    h+= deltaY;

    return h;
}

void Node::CalculateNeighbour()
{
    switch (nodeDirection)
    {
        case north :
            children.emplace_back(Node(Coordinate(coordinate.x, coordinate.y + 1), north, this, 1));
            children.emplace_back(Node(coordinate, south, this, 3));
            children.emplace_back(Node(coordinate, east, this, 3));
            children.emplace_back(Node(coordinate, west, this, 3));
            break;
        case south :
            children.emplace_back(Node(coordinate, north, this, 3));
            children.emplace_back(Node(Coordinate(coordinate.x, coordinate.y - 1), south, this, 1));
            children.emplace_back(Node(coordinate, east, this, 3));
            children.emplace_back(Node(coordinate, west, this, 3));
            break;
        case east :
            children.emplace_back(Node(coordinate, north, this, 3));
            children.emplace_back(Node(coordinate, south, this, 3));
            children.emplace_back(Node(Coordinate(coordinate.x + 1, coordinate.y), east, this, 1));
            children.emplace_back(Node(coordinate, west, this, 3));
            break;
        case west :
            children.emplace_back(Node(coordinate, north, this, 3));
            children.emplace_back(Node(coordinate, south, this, 3));
            children.emplace_back(Node(coordinate, east, this, 3));
            children.emplace_back(Node(Coordinate(coordinate.x - 1, coordinate.y), west, this, 1));
            break;
        default:
            argos::LOGERR << "CalculateNeighbour nodeDirection switch -> default. You shouldn't be here." << std::endl;
            break;
    }
}

Node* Node::LeastCost() // TODO: change name to describe functionality
{
    if(children.empty())
    {
        return this;
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

#endif