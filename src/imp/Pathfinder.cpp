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
    //argos::LOG << "Find path from: " << start.x << "," << start.y << ". to: " << end.x << "," << end.y << std::endl;

    switch (selectedAlgorithm)
    {
        case 0:
            p = GetStupidPath(start, end);
            break;

        case 1:
            p = GetAstarPath(startTick, start, end, currentDirection, isCarrying, em);
            break;

        case 2:
            argos::LOG << currentDirection << std::endl;
            p = GetSemiStupidPath(start, end, currentDirection, startTick, em);
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

Path Pathfinder::GetSemiStupidPath(Coordinate start, Coordinate end, direction dir, int startTick, EnvironmentManager* _em, int straightTime, int turnTime, int waitTime)
{
    Path newPath;
    switch (dir)
    {
        case north :
            argos::LOG << "north" << std::endl;

            if(start.y < end.y){
                newPath.AddWayPoint(Coordinate(start.x, end.y), start);
            }
            else {
                newPath.AddWayPoint(Coordinate(end.x, start.y), start);
            }
            break;
        case south :
            argos::LOG << "south" << std::endl;

            if(start.y < end.y){
                newPath.AddWayPoint(Coordinate(end.x, start.y), start);
            }
            else {
                newPath.AddWayPoint(Coordinate(start.x, end.y), start);
            }
            break;
        case east :
            argos::LOG << "east" << std::endl;

            if(start.x < end.x){
                newPath.AddWayPoint(Coordinate(end.x, start.y), start);
            }
            else {
                newPath.AddWayPoint(Coordinate(start.x, end.y), start);
            }
            break;
        case west :
            argos::LOG << "west" << std::endl;

            if(start.x < end.x){
                newPath.AddWayPoint(Coordinate(start.x, end.y), start);
            }
            else {
                newPath.AddWayPoint(Coordinate(end.x, start.y), start);
            }
            break;
        default:
            argos::LOGERR << "default. You shouldn't be here." << std::endl;
            break;

    }
    newPath = AddWaits(newPath, start, startTick, _em, straightTime, turnTime, waitTime);
    newPath.AddWayPoint(Coordinate(end.x, end.y), Coordinate(end.x, start.y));

    return newPath;
}

Path Pathfinder::GetAstarPath(int _startTick, Coordinate start, Coordinate goal, direction _direction, bool isCarrying, EnvironmentManager* _environmentManager, int straightTime, int turnTime, int waitTime)
{
    int startTick = _startTick;
    Node* startNode = new Node(start, _direction); // TODO: remove from heap when path is done
    Node* currentNode;
    environmentManager = _environmentManager;

    for (int i = 0; i < 250; i++)
    {
        //Find the leaf with the lowest cost
        currentNode = startNode->LeastCost();

        //Flag to ensure that a nodes children compare to the first child
        bool flag = true;

        //argos::LOG<< currentNode->coordinate.x << "," << currentNode->coordinate.y << std::endl;

        //Check if the node is goal node
        if ((currentNode->coordinate.x == goal.x) && (currentNode->coordinate.y == goal.y))
        {
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
                        node.lowestCost = node.fScore;

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

Path Pathfinder::AddWaits(Path p, Coordinate start, int startTick, EnvironmentManager* em, int straightTime, int turnTime, int waitTime) {

    Coordinate first = p.waypoints.front();
    Coordinate second = p.waypoints.back();
    int currentTime = startTick;

    if(start.x == first.x){
        if(start.y < first.y){
            AddWaitsNorth(p, start, first, startTick, em, straightTime, turnTime, waitTime);
        }else{
            AddWaitsSouth(p, start, first, startTick, em, straightTime, turnTime, waitTime);
        }

        if(start.x < second.x){
            AddWaitsEast(p, first, second, startTick, em, straightTime, turnTime, waitTime);
        }else{
            AddWaitsWest(p, first, second, startTick, em, straightTime, turnTime, waitTime);
        }

    }else{
        if(start.x < first.x){
            AddWaitsEast(p, start, first, startTick, em, straightTime, turnTime, waitTime);
        }else{
            AddWaitsWest(p, start, first, startTick, em, straightTime, turnTime, waitTime);
        }

        if(start.y < second.y){
            AddWaitsNorth(p, first, second, startTick, em, straightTime, turnTime, waitTime);
        }else{
            AddWaitsSouth(p, first, second, startTick, em, straightTime, turnTime, waitTime);
        }
    }

    return Path();
}

std::pair<Path, int>
Pathfinder::AddWaitsNorth(Path p, Coordinate start, Coordinate _end, int startTick, EnvironmentManager* _em, int straightTime,
                          int turnTime, int waitTime) {

    Coordinate end = _end;
    int currentTime = startTick;
    bool flag = false;
    int _wait = 0;

    for(int i = start.y+1; i<= end.y; i++){
        while(_em->IsReserved(Coordinate(start.x, i), currentTime, startTick+straightTime)){
            flag = true;
            _wait += waitTime;
            currentTime+=waitTime;
        }
        if(flag){
            p.AddWayPoint(Coordinate(-1, _wait), Coordinate(start.x, i-1));
            flag = false;
            _wait = 0;
        }
        currentTime += straightTime;
    }
    currentTime += turnTime;

    return std::pair<Path, int>(p, currentTime);
}

std::pair<Path, int>
Pathfinder::AddWaitsSouth(Path p, Coordinate start, Coordinate _end, int startTick, EnvironmentManager* _em, int straightTime,
                          int turnTime, int waitTime) {

    Coordinate end = _end;
    int currentTime = startTick;
    bool flag = false;
    int _wait = 0;

    for(int i = start.y-1; i>= end.y; i--){
        while(_em->IsReserved(Coordinate(start.x, i), currentTime, startTick+straightTime)){
            flag = true;
            _wait += waitTime;
            currentTime+=waitTime;
        }
        if(flag){
            p.AddWayPoint(Coordinate(-1, _wait), Coordinate(start.x, i+1));
            flag = false;
        }
        currentTime += straightTime;
    }
    currentTime += turnTime;

    return std::pair<Path, int>(p, currentTime);
}

std::pair<Path, int>
Pathfinder::AddWaitsEast(Path p, Coordinate start, Coordinate _end, int startTick, EnvironmentManager* _em, int straightTime,
                         int turnTime, int waitTime) {

    Coordinate end = _end;
    int currentTime = startTick;
    bool flag = false;
    int _wait = 0;

    for(int i = start.x + 1; i<= end.x; i++){
        while(_em->IsReserved(Coordinate(i, start.y), currentTime, startTick+straightTime)){
            flag = true;
            _wait += waitTime;
            currentTime+=waitTime;
        }
        if(flag){
            p.AddWayPoint(Coordinate(-1, _wait), Coordinate(i-1, start.y));
            flag = false;
        }
        currentTime += straightTime;
    }
    currentTime += turnTime;

    return std::pair<Path, int>(p, currentTime);
}

std::pair<Path, int>
Pathfinder::AddWaitsWest(Path p, Coordinate start, Coordinate _end, int startTick, EnvironmentManager* _em, int straightTime,
                         int turnTime, int waitTime) {

    Coordinate end = _end;
    int currentTime = startTick;
    bool flag = false;
    int _wait = 0;

    for(int i = start.x - 1; i>= end.x; i--){
        while(_em->IsReserved(Coordinate(i, start.y), currentTime, startTick+straightTime)){
            flag = true;
            _wait += waitTime;
            currentTime+=waitTime;
        }
        if(flag){
            p.AddWayPoint(Coordinate(-1, _wait), Coordinate(i+1, start.y));
            flag = false;
        }
        currentTime += straightTime;
    }
    currentTime += turnTime;

    return std::pair<Path, int>(p, currentTime);
}


#endif