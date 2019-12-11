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
    argos::LOG << "Find path from: " << start.x << "," << start.y << ". to: " << end.x << "," << end.y << std::endl;

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
    

    // reserve timeslots;
    if (!p.waypoints.empty())
    {
        // this assumes that selected algorithm has checked for bookings
        ReserveTimeslotsForPath(startTick, lastDirection, start, p);
    }
    else
    {
        argos::LOGERR << "The path returned is empty." << std::endl;
        pathReturnedEmpty++;
    }

    return p;
}

int Pathfinder::ReserveTimeslotsForPath(int startTick, direction startDirection, Coordinate startCoord, Path path)
{
    // ignore timeslot startTick in startCoord since it should already be reserved

    bool isSuccessfull = false;

    typedef std::pair<Coordinate, std::pair<int,int>> cTS;
    typedef std::pair<int,int> tt;

    std::queue <std::pair<Coordinate, std::pair<int,int>>> timeSlotToReserveDubs;

    Coordinate l = startCoord;
    Coordinate n;
    int TC = startTick;
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
        if (nd == ld) // doesn't need to turn.
        {
            argos::LOG << "Doesn't need to turn." << std::endl;
        }
        else // need to turn. 
        {
            int d = (nd + ld)%4;
            if (d==2)
            {
                //180 turn
                argos::LOG << "Turn 180. Plus ticks: " << ticksToTurn180degrees << std::endl;
                argos::LOG << "Coord to reserve: ";
                l.PrintCoordinate();
                argos::LOG << " in tick: " << TC << " to tick: "<< TC+ticksToTurn180degrees <<std::endl;

                timeSlotToReserveDubs.push(cTS(l, tt(TC,TC+ticksToTurn180degrees)));
                TC += ticksToTurn180degrees;
            }
            else
            {
                //90 turn
                argos::LOG << "Turn 90. Plus ticks: " << ticksToTurn90degrees << std::endl;

                argos::LOG << "Coord to reserve: ";
                l.PrintCoordinate();
                argos::LOG << " in tick: " << TC << " to tick: "<< TC+ticksToTurn90degrees <<std::endl;

                timeSlotToReserveDubs.push(cTS(l, tt(TC,TC+ticksToTurn90degrees)));
                TC += ticksToTurn90degrees;
            }         
        }

        // check if x or y
        xdiff = l.x-n.x;

        if(xdiff!=0) // travelling on x-axis
        {
            int savex = l.x;

            if(xdiff<0) // traveling in positive direction
            {
                while(xdiff!=0) //xdiff is negative
                {
                    //argos::LOG << "xdiff in loop --> : " << xdiff << std::endl;
                    n = Coordinate(l.x+1, l.y);
                    TC += ticksToMoveOneCell;

                    argos::LOG << "Coord to reserve: ";
                    l.PrintCoordinate();
                    argos::LOG << " in tick: " << TC<< std::endl;
                    argos::LOG << "Coord to reserve: ";
                    n.PrintCoordinate();
                    argos::LOG << " in tick: " << TC<< std::endl;

                    timeSlotToReserveDubs.push(cTS(l, tt(TC,TC)));
                    timeSlotToReserveDubs.push(cTS(n, tt(TC,TC)));
                    l = Coordinate(n.x, n.y);
                    xdiff++;
                }
            }
            else // traveling in negative direction
            {
                while(xdiff!=0) // xdiff is positive
                {
                    //argos::LOG << "xdiff in loop <-- : " << xdiff << std::endl;
                    n = Coordinate(l.x-1, l.y);
                    TC += ticksToMoveOneCell;

                    argos::LOG << "Coord to reserve: ";
                    l.PrintCoordinate();
                    argos::LOG << " in tick: " << TC<< std::endl;
                    argos::LOG << "Coord to reserve: ";
                    n.PrintCoordinate();
                    argos::LOG << " in tick: " << TC<< std::endl;

                    timeSlotToReserveDubs.push(cTS(l, tt(TC,TC)));
                    timeSlotToReserveDubs.push(cTS(n, tt(TC,TC)));
                    l = Coordinate(n.x, n.y);
                    xdiff--;
                }
            }
            //l = n;
            //l.x = savex;
            argos::LOG << "last x: " << l.x << std::endl;
            argos::LOG << "next x: " << n.x << std::endl;
            path.waypoints.pop();
            continue;
        }

        ydiff = l.y-n.y;

        if(ydiff!=0) // traveling on y-axis
        {
            if(ydiff<0) // traveling in positive direction
            {
                while(ydiff!=0)
                {
                    //argos::LOG << "ydiff: --> " << ydiff << std::endl;
                    n = Coordinate(l.x, l.y+1);
                    TC += ticksToMoveOneCell;

                    argos::LOG << "Coord to reserve: ";
                    l.PrintCoordinate();
                    argos::LOG << " in tick: " << TC<< std::endl;
                    argos::LOG << "Coord to reserve: ";
                    n.PrintCoordinate();
                    argos::LOG << " in tick: " << TC<< std::endl;

                    timeSlotToReserveDubs.push(cTS(l, tt(TC,TC)));
                    timeSlotToReserveDubs.push(cTS(n, tt(TC,TC)));
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

                    argos::LOG << "Coord to reserve: ";
                    l.PrintCoordinate();
                    argos::LOG << " in tick: " << TC<< std::endl;
                    argos::LOG << "Coord to reserve: ";
                    n.PrintCoordinate();
                    argos::LOG << " in tick: " << TC<< std::endl;

                    timeSlotToReserveDubs.push(cTS(l, tt(TC,TC)));
                    timeSlotToReserveDubs.push(cTS(n, tt(TC,TC)));
                    l = Coordinate(n.x, n.y);
                    ydiff++;
                }
            }
        }
        else{
            argos::LOGERR << "Error in PF::ReserveTimeSlotsForPath." << std::endl;
        }
        l = n;
        path.waypoints.pop();
    }
    
    //remove dubs before reserving
    std::set <std::pair<int, std::pair<int,int>>> timeSlotToReserve;

    std::pair<Coordinate, std::pair<int,int>> nextValue;
    Coordinate nextCoord;
    int firstTick;
    int secondTick;


    while(!timeSlotToReserveDubs.empty())
    {
        nextValue = timeSlotToReserveDubs.front();
        nextCoord = nextValue.first;
        firstTick = nextValue.second.first;
        secondTick = nextValue.second.second;
        
        while (firstTick<secondTick)
        {
            if(timeSlotToReserve.find(std::pair<int, tt>(firstTick, tt(nextCoord.x,nextCoord.y))) == timeSlotToReserve.end())
            {
                //dublicate. TODO: refactor 
                argos::LOG << "dublicate" << std::endl;
            }
            else{
                timeSlotToReserve.insert(std::pair<int, tt>(firstTick, tt(nextCoord.x,nextCoord.y)));
            }
            firstTick += 20; //em->numberOfTicksPerTimeslot; TODO
        }

        timeSlotToReserveDubs.pop();
    }
    
    for(auto t : timeSlotToReserve)
    {
        argos::LOG << "Timeslot to reserve: " << t.first << ". x: "<< t.second.first << " . y: " << t.second.second << std::endl;
    }


    ///////////////////


    // Reserve timeslots
    /* TODO uncomment
    while(!timeSlotToReserve.empty())
    {
        std::pair<Coordinate, std::pair<int,int>> n = timeSlotToReserve.front();
        isSuccessfull = em->ReserveCell(n.first, n.second.first, n.second.second);
        timeSlotToReserve.pop();
    }*/

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
    Node* startNode = new Node(start, _direction); // TODO: remove from heap when path is done
    currentNode = startNode;
    int i = 0;

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