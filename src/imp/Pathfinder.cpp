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
    p.arriveAtTick = startTick;
     
    switch (selectedAlgorithm)
    {
        case 0:
            p = GetStupidPath(start, end);
            break;

        case 1:
            p = GetAstarPath(start, end, lastDirection, isCarrying); 
            break;
        
        default:
            break;
    }
    
    int nextTick = startTick;
    /*
    // reserve timeslots;
    if (!p.waypoints.empty())
    {
        nextTick = ReserveTimeslotsForPath(nextTick, lastDirection, start, p);
        // this assumes that selected algorithm has checked for bookings
        
    }
    else
    {
        argos::LOGERR << "The path returned is empty." << std::endl;
        pathReturnedEmpty++;
    }
    if(nextTick != startTick){p.arriveAtTick=nextTick;}
    */
   
    return p;
}

int Pathfinder::ReserveTimeslotsForPath(int startTick, direction startDirection, Coordinate startCoord, Path path)
{
    // ignore timeslot startTick in startCoord since it should already be reserved

    typedef std::pair<Coordinate, int> cTS;
    typedef std::pair<int,int> tt;

    int TC = startTick;

    std::queue <std::pair<Coordinate, int>> timeSlotToReserveDubs;

    Coordinate l = startCoord;
    Coordinate n;

    direction ld = startDirection;
    direction nd;

    int xdiff = 0;
    int ydiff = 0;

    // Generate list of timeslots to be reserved
    while(!path.waypoints.empty())
    {
        n = path.waypoints.front();
        
        // check if need to turn
        nd = RobotWrapper::GetFaceTowardsInstruction(n, l, ld);
        if (nd == ld){} // doesn't need to turn.
        else // need to turn. 
        {
            int d = (nd + ld)%4;
            if (d==2) //180 turn
            {
                timeSlotToReserveDubs.push(cTS(l, TC));
                timeSlotToReserveDubs.push(cTS(l, TC+ticksToTurn90degrees));
                timeSlotToReserveDubs.push(cTS(l, TC+ticksToTurn180degrees));
                TC += ticksToTurn180degrees;
            }
            else //90 turn
            {
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
                    n = Coordinate(l.x, l.y+1);
                    TC += ticksToMoveOneCell;

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
                    n = Coordinate(l.x, l.y-1);
                    TC += ticksToMoveOneCell;

                    timeSlotToReserveDubs.push(cTS(l, TC));
                    timeSlotToReserveDubs.push(cTS(n, TC));
                    l = Coordinate(n.x, n.y);
                    ydiff++;
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

Path Pathfinder::GetAstarPath(Coordinate start, Coordinate goal, direction _direction, bool isCarrying) 
{
    Node* startNode = new Node(start, _direction);
    currentNode = startNode;
    int i = 0;

    for (int i = 0; i < 100; i++)
    {
        //Find the leaf with the lowest cost
        currentNode = startNode->LeastCost();
        bool flag = true;

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