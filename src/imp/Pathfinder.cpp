#ifndef PATHFINDER_CPP
#define PATHFINDER_CPP


Pathfinder::Pathfinder()
{
    selectedAlgorithm = 0;
}
Pathfinder::~Pathfinder(){}

Path Pathfinder::FindPath(Coordinate start, Coordinate end, direction currentDirection, bool isCarrying, EnvironmentManager* _environmentM)
{
    Path p; 
    argos::LOG << "Find path from: " << start.x << "," << start.y << ". to: " << end.x << "," << end.y << std::endl;

    switch (selectedAlgorithm)
    {
        case 0:
            p = GetStupidPath(start, end);
            break;

        case 1:
            p = GetAstarPath(start, end, currentDirection, isCarrying, _environmentM);
            break;
        
        default:
            break;
    }
    
    if (p.waypoints.empty())
    {
        argos::LOG << "The path returned is empty." << std::endl;
        pathReturnedEmpty++;
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

Path Pathfinder::GetAstarPath(Coordinate start, Coordinate goal, direction _direction, bool isCarrying, EnvironmentManager* _environmentManager, int straightTime, int turnTime, int waitTime)
{
    environmentManager = _environmentManager;
    Node* startNode = new Node(start, _direction); // TODO: remove from heap when path is done
    currentNode = startNode;
    int i = 0;

    for (int i = 0; i < 500; i++)
    {
        //Find the leaf with the lowest cost
        currentNode = startNode->LeastCost();

        //Flag to ensure that a nodes children compare to the first child
        bool flag = true;

        argos::LOG<< currentNode->coordinate.x << currentNode->coordinate.y << std::endl;

        argos::LOG<< currentNode->children.size() << std::endl;

        if(currentNode->start){
            argos::LOG<< "FACK" << std::endl;

        }


        //Check if the node is goal node
        if ((currentNode->coordinate.x == goal.x) && (currentNode->coordinate.y == goal.y))
        {
               return ReversePath((*currentNode), pathList);
        }

        //Calculate neighbors of the node, should always be true, since currentNode is always a leaf
        if (currentNode->children.empty())
        {
            currentNode->CalculateNeighbour(straightTime, turnTime, waitTime, environmentManager);
            
            for (Node node : currentNode->children)
            {
                node.gScore = currentNode->gScore + node.parentWeight;
                node.fScore = node.gScore + node.CalculateHeuristic(goal, turnTime);
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
    argos::LOGERR << "Path not found within a reasonable time" << std::endl;

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
        /*environmentManager->ReserveCell(node.coordinate,
                environmentManager->tickCounter+(node.parent->gScore*10),
                environmentManager->tickCounter+(node.gScore*10)+1);
                */
        path.emplace_back(node.coordinate, node.parent->coordinate);

        return ConstructPath((*node.parent), path);
    }
}


#endif