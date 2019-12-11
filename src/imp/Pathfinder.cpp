#ifndef PATHFINDER_CPP
#define PATHFINDER_CPP

Pathfinder::Pathfinder(EnvironmentManager* _em):em(_em)
{
    selectedAlgorithm = 1;
}
Pathfinder::~Pathfinder(){}

Path Pathfinder::FindPath(int startTick, Coordinate start, Coordinate end, direction currentDirection, bool isCarrying)
{
    Path p; 
    argos::LOG << "Find path from: " << start.x << "," << start.y << ". to: " << end.x << "," << end.y << std::endl;

    switch (selectedAlgorithm)
    {
        case 0:
            p = GetStupidPath(start, end);
            break;

        case 1:
            p = GetAstarPath(startTick, start, end, currentDirection, isCarrying, em);
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

Path Pathfinder::GetAstarPath(int _startTick, Coordinate start, Coordinate goal, direction _direction, bool isCarrying, EnvironmentManager* _environmentManager, int straightTime, int turnTime, int waitTime)
{
    int startTick = _startTick;
    Node* startNode = new Node(start, _direction); // TODO: remove from heap when path is done
    Node* currentNode;
    environmentManager = _environmentManager;

    int i = 0;

    for (int i = 0; i < 250; i++)
    {
        //Find the leaf with the lowest cost
        currentNode = startNode->LeastCost();

        //Flag to ensure that a nodes children compare to the first child
        bool flag = true;


        argos::LOG<< currentNode->coordinate.x << currentNode->coordinate.y << std::endl;

        /*

        if(!currentNode->start){
            argos::LOG<< "My children: " <<currentNode->children.size() << std::endl;

            argos::LOG<< "Parent children: "<<currentNode->parent->children.size() << std::endl;

        }*/


        //Check if the node is goal node
        if ((currentNode->coordinate.x == goal.x) && (currentNode->coordinate.y == goal.y))
        {
            argos::LOGERR << "PATH FOUND";
               return ReversePath((*currentNode));
        }

        //Calculate neighbors of the node, should always be true, since currentNode is always a leaf
        if (currentNode->children.empty())
        {
            if(currentNode->CalculateNeighbour(startTick, straightTime, turnTime, waitTime, environmentManager)){
                for (Node& node : currentNode->children)
                {
                    if(!node.deleteNode){

                        node.gScore = currentNode->gScore + node.parentWeight;
                        node.fScore = node.gScore + node.CalculateHeuristic(goal, turnTime, straightTime);

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
            else{
                currentNode->deleteNode = true;
                currentNode->fScore = 100000000;
            }
        }
    }
    argos::LOGERR << "Path not found within a reasonable time" << std::endl;

    return Path();
}

Path Pathfinder::ReversePath(Node node)
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
        Node* temp;

        /*if(node.isWait){
            temp = node.calculateWaitTime();
            path.emplace_back(Coordinate(-1,abs(node.gScore-temp->gScore)*10), temp->parent->coordinate);
            return ConstructPath((*temp->parent), path);


        }else {*/
            path.emplace_back(node.coordinate, node.parent->coordinate);
            return ConstructPath((*node.parent), path);

        //}
    }
}


#endif