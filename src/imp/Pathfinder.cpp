#ifndef PATHFINDER_CPP
#define PATHFINDER_CPP

Pathfinder::Pathfinder(EnvironmentManager* _em):em(_em)
{
    selectedAlgorithm = 0;
}
Pathfinder::~Pathfinder(){}

Path Pathfinder::FindPath(int startTick, Coordinate start, Coordinate end, direction lastDirection, bool isCarrying)
{
    Path p;
    p = Path();
    p.arriveAtTick = startTick; // to make sure returned path has an arriveAtTick value.
    
    if((start.x == end.x) && (start.y == end.y))
    {
        argos::LOGERR << "You are already there." << std::endl;
        return p;
    }

    switch (selectedAlgorithm)
    {
        case 0:
            p = GetStupidPath(start, end);
            break;

        case 1:
            p = GetAstarPath(startTick, start, end, lastDirection, isCarrying, em);
            break;
        
        default:
            break;
    }

    int arriveAtTick = startTick;

    // reserve timeslots;
    if (!p.waypoints.empty())
    {
        // this assumes that selected algorithm has checked for bookings
        arriveAtTick = ReserveTimeslotsForPath(startTick, lastDirection, start, p);
    }
    else
    {
        argos::LOGERR << "The path returned is empty." << std::endl;
        pathReturnedEmpty++;
    }

    if(arriveAtTick != startTick){p.arriveAtTick=arriveAtTick;}

    return p;
}

int Pathfinder::ReserveTimeslotsForPath(int startTick, direction startDirection, Coordinate startCoord, Path path)
{
    // ignore timeslot startTick in startCoord since it should already be reserved
    if(startTick < em->tickCounter)
    {
        startTick=em->tickCounter;
    } // not good enough
    startTick++;

    typedef std::pair<Coordinate, int> cTS;
    typedef std::pair<int,int> tt;

    int TC = startTick;

    std::queue <std::pair<Coordinate, int>> timeSlotToReserveDubs;

    Coordinate l = startCoord; //lastCoord
    Coordinate n;               //nextCoord

    direction ld = startDirection;  //lastDirection
    direction nd;   //nextDirection

    // for finding whither going on x or y -axis
    int xdiff = 0;
    int ydiff = 0;

    // Generate list of timeslots to be reserved
    while(!path.waypoints.empty())
    {
        n = path.waypoints.front();

        // check if need to turn
        nd = RobotWrapper::GetFaceTowardsInstruction(n, l, ld);
        if (nd == ld) // doesn't need to turn.
        {
            //argos::LOG << "Doesn't need to turn." << std::endl;
        }
        else // need to turn.
        {
            int d = (nd + ld)%4;
            if (d==2) //180 turn
            {
                //argos::LOG << "Turn 180. Plus ticks: " << ticksToTurn180degrees << std::endl;
                //argos::LOG << "Coord to reserve: "; l.PrintCoordinate(); argos::LOG << " in tick: " << TC << std::endl;
                //argos::LOG << "Coord to reserve: "; l.PrintCoordinate(); argos::LOG << " in tick: " << TC+ticksToTurn90degrees << std::endl;
                //argos::LOG << "Coord to reserve: "; l.PrintCoordinate(); argos::LOG << " in tick: " << TC+ticksToTurn180degrees << std::endl;

                timeSlotToReserveDubs.push(cTS(l, TC));
                timeSlotToReserveDubs.push(cTS(l, TC+ticksToTurn90degrees));
                timeSlotToReserveDubs.push(cTS(l, TC+ticksToTurn180degrees));
                TC += ticksToTurn180degrees;
            }
            else //90 turn
            {
                //argos::LOG << "Turn 90. Plus ticks: " << ticksToTurn90degrees << std::endl;
                //argos::LOG << "Coord to reserve: "; l.PrintCoordinate(); argos::LOG << " in tick: " << TC << std::endl;
                //argos::LOG << "Coord to reserve: "; l.PrintCoordinate(); argos::LOG << " in tick: " << TC+ticksToTurn90degrees << std::endl;

                timeSlotToReserveDubs.push(cTS(l, TC));
                timeSlotToReserveDubs.push(cTS(l, TC+ticksToTurn90degrees));
                TC += ticksToTurn90degrees;
            }
        }

        // check if x or y
        xdiff = l.x-n.x;
        ydiff = l.y-n.y;

        if(xdiff == 0 && ydiff == 0) // going nowhere
        {
            argos::LOGERR << "Error in PF::ReserveTimeSlotsForPath. Both xdiff and ydiff are zero." << std::endl;
        }

        if(xdiff!=0) // travelling on x-axis
        {
            int savex = l.x;

            if(xdiff<0) // traveling in positive direction
            {
                while(xdiff!=0) //xdiff is negative
                {
                    n = Coordinate(l.x+1, l.y);
                    TC += ticksToMoveOneCell;

                    //argos::LOG << "Coord to reserve: "; l.PrintCoordinate(); argos::LOG << " in tick: " << TC<< std::endl;
                    //argos::LOG << "Coord to reserve: "; n.PrintCoordinate(); argos::LOG << " in tick: " << TC<< std::endl;

                    timeSlotToReserveDubs.push(cTS(l, TC));
                    timeSlotToReserveDubs.push(cTS(n, TC));
                    l = Coordinate(n.x, n.y);
                    xdiff++;
                }
            }
            else // traveling in negative direction
            {
                while(xdiff!=0) // xdiff is positive
                {
                    n = Coordinate(l.x-1, l.y);
                    TC += ticksToMoveOneCell;

                    //argos::LOG << "Coord to reserve: "; l.PrintCoordinate(); argos::LOG << " in tick: " << TC<< std::endl;
                    //argos::LOG << "Coord to reserve: "; n.PrintCoordinate(); argos::LOG << " in tick: " << TC<< std::endl;

                    timeSlotToReserveDubs.push(cTS(l, TC));
                    timeSlotToReserveDubs.push(cTS(n, TC));
                    l = Coordinate(n.x, n.y);
                    xdiff--;
                }
            }

            path.waypoints.pop();
            continue;
        }

        if(ydiff!=0) // traveling on y-axis
        {
            if(ydiff<0) // traveling in positive direction
            {
                while(ydiff!=0)
                {
                    //argos::LOG << "ydiff: --> " << ydiff << std::endl;
                    n = Coordinate(l.x, l.y+1);
                    TC += ticksToMoveOneCell;

                    //argos::LOG << "Coord to reserve: "; l.PrintCoordinate(); argos::LOG << " in tick: " << TC<< std::endl;
                    //argos::LOG << "Coord to reserve: "; n.PrintCoordinate(); argos::LOG << " in tick: " << TC<< std::endl;

                    timeSlotToReserveDubs.push(cTS(l, TC));
                    timeSlotToReserveDubs.push(cTS(n, TC));
                    l = Coordinate(n.x, n.y);
                    ydiff++;
                }
            }
            else // traveling in negative direction
            {
                while(ydiff!=0)
                {
                    //argos::LOG << "ydiff: " << ydiff << std::endl;
                    n = Coordinate(l.x, l.y-1);
                    TC += ticksToMoveOneCell;

                    //argos::LOG << "Coord to reserve: "; l.PrintCoordinate(); argos::LOG << " in tick: " << TC<< std::endl;
                    //argos::LOG << "Coord to reserve: "; n.PrintCoordinate(); argos::LOG << " in tick: " << TC<< std::endl;

                    timeSlotToReserveDubs.push(cTS(l, TC));
                    timeSlotToReserveDubs.push(cTS(n, TC));
                    l = Coordinate(n.x, n.y);
                    ydiff--;
                }
            }
        }

        l = n; // set last coord.

        path.waypoints.pop();
    }

    //remove dubs before reserving
    std::set <std::pair <int, tt>> timeSlotToReserve;

    cTS nextValue;
    Coordinate nextCoord;
    int nextTick;

    while(!timeSlotToReserveDubs.empty())
    {
        nextValue = timeSlotToReserveDubs.front();
        nextCoord = nextValue.first;
        nextTick = nextValue.second;

        // check if timereservation is in timeToReserve
        if(timeSlotToReserve.find(std::pair <int, tt>(nextTick, tt(nextCoord.x, nextCoord.y))) == timeSlotToReserve.end())
        {
            //argos::LOG << "In tick:" << nextTick << ". Reserve: "; nextCoord.PrintCoordinate();  argos::LOG << std::endl;
            timeSlotToReserve.insert(std::pair<int, tt>(nextTick, tt(nextCoord.x, nextCoord.y)));
        }
        else
        {
            //argos::LOG << "DUB. In tick:" << nextTick << ". Reserve: " <<nextCoord.x<<","<<nextCoord.y << std::endl;
        }

        timeSlotToReserveDubs.pop();
    }

    for(auto t : timeSlotToReserve)
    {
       //argos::LOG << "Reserve tick: " << t.first << ". x: "<< t.second.first << " . y: " << t.second.second << std::endl;
       em->ReserveCell(Coordinate(t.second.first, t.second.second), t.first, t.first);
    }

    return TC;
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
    EnvironmentManager* environmentManager;
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