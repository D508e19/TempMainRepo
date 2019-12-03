#ifndef PATHFINDER_CPP
#define PATHFINDER_CPP

Pathfinder::Pathfinder()
{
    selectedAlgorithm = 1;
}
Pathfinder::~Pathfinder(){}

Path Pathfinder::FindPath(Coordinate start, Coordinate end, direction currentDirection)
{
    Path p; 
    //argos::LOG << "Find path from: " << start.x << "," << start.y << ". to: " << end.x << "," << end.y << std::endl;

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
        argos::LOG << "The path returned is empty." << std::endl;
    }

    return p;
}

Path Pathfinder::GetStupidPath(Coordinate start, Coordinate end)
{
    Path newPath;

    newPath.AddWayPoint(Coordinate(end.x, start.y), start);
    newPath.AddWayPoint(Coordinate(end.x, end.y), Coordinate(end.x, start.y));

    return newPath;
}

Path Pathfinder::GetAstarPath(Coordinate start, Coordinate goal, direction _direction) 
{
    Node* startNode = new Node(start, _direction);
    currentNode = startNode;
    int i = 0;
    argos::LOG << currentNode->nodeDirection << std::endl;

    for (int i = 0; i < 100; i++)
    {
        //Find the leaf with the lowest cost
        currentNode = startNode->LeastCost();
        bool flag = true; // flag for hvad??

        //Check if the node is goal node
        if ((currentNode->coordinate.x == goal.x) && (currentNode->coordinate.y == goal.y))
        {
               return ReversePath((*currentNode), pathList);
        }

        //Calculate neighbors of the node, should always be true, since currentNode is always a leaf
        if (currentNode->children.empty())
        {
            currentNode->CalculateNeighbour();
            
            for (Node node : currentNode->children)
            {
                node.gScore = currentNode->gScore + node.parentWeight;
                node.fScore = node.gScore + node.CalculateHeuristic(goal);
                if(flag)
                {
                    currentNode->lowestCost = node.fScore;
                    flag = false;
                }
                else if(node.fScore < currentNode->lowestCost)
                {
                    currentNode->lowestCost = node.fScore;
                }
            }
        }
    } 
    return pathList;
}

Path Pathfinder::ReversePath(Node node, Path path)
{
    simplePath wrong;
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
        path.emplace_back(node.coordinate, node.parent->coordinate);

        return ConstructPath((*node.parent), path);
    }
}


#endif