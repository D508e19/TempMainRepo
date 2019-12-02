#ifndef PATHFINDER_CPP
#define PATHFINDER_CPP

Pathfinder::Pathfinder()
{
    selectedAlgorithm = 0;
}
Pathfinder::~Pathfinder(){}

Path Pathfinder::FindPath(Coordinate start, Coordinate end, direction currentDirection)
{
    Path p; 
    argos::LOG << "Find path from: " << start.x << "," << start.y << ". to: " << end.x << "," << end.y << std::endl;

    switch (selectedAlgorithm)
    {
        case 0:
            p = GetStupidPath(start, end);
            break;

        case 1:
            p = GetAstarPath(start, end, currentDirection);
            break;
        
        default:
            break;
    }
    
    if (p.waypoints.empty())
    {
        argos::LOG << "path empty." << std::endl;
    }
    //argos::LOG << p.waypoints.front().x <<","<<p.waypoints.front().y<<std::endl;
    return p;
};

Path Pathfinder::GetStupidPath(Coordinate start, Coordinate end)
{
    //std::cout << "From: " << start.x << ", " << start.y << std::endl;
    //std::cout << "Want to go to: " << end.x << ", " << end.y << std::endl;
   
    Path newPath;

    newPath.AddWayPoint(Coordinate(end.x, start.y), start);
    newPath.AddWayPoint(Coordinate(end.x, end.y), Coordinate(end.x, start.y));

    return newPath;
}

Path Pathfinder::GetAstarPath(Coordinate start, Coordinate goal, direction d) 
{
    Node* startNode = new Node(start,d);
    current = startNode;
    int i = 0;

    do {
        //Find the leaf with the lowest cost
        current = (*startNode).leastCost();
        bool flag = true;

        //Check if the node is goal node
        if (((*current).coordinate.x == goal.x) && ((*current).coordinate.y == goal.y)){
               return PathConstructer((*current), pathList);
        }
        //Calculate neighbors of the node, should always be true, since current is always a leaf
        if ((*current).children.empty()){

            (*current).calculateNeighbour();

            for (Node n : (*current).children){
                n.gScore = (*current).gScore + n.parentWeight;
                n.fScore = n.gScore + n.heuristic(goal);
                if(flag){
                    (*current).lowestCost = n.fScore;
                    flag = false;
                }
                else if(n.fScore < (*current).lowestCost){
                    (*current).lowestCost = n.fScore;
                }
            }
        }

        //Iterate through neighbors to find the best neighbor
        i++;
    } 
    while (i<100);

    return pathList;
}

Path Pathfinder::PathConstructer(Node node, Path path)
{
    std::list<std::pair<Coordinate, Coordinate>> wrong;
    Path right;
    std::pair<Coordinate, Coordinate> pair;

    wrong = ConstructPath(node, wrong);

    while (!wrong.empty()){
        pair = wrong.back();
        wrong.pop_back();
        right.AddWayPoint(pair.first, pair.second);
    }

    return right;
}

simplePath Pathfinder::ConstructPath(Node node, simplePath path) 
{
    if(node.start){
        return path;
    }
    else {
        path.emplace_back(node.coordinate, (*node.parent).coordinate);

        return ConstructPath((*node.parent), path);
    }
}


#endif