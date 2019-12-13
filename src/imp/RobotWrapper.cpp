#ifndef ROBOTWRAPPER_CPP
#define ROBOTWRAPPER_CPP

#include "src/argos/controllers/basicbot/basicbot.h"

RobotWrapper::RobotWrapper(){};
RobotWrapper::~RobotWrapper(){};

RobotWrapper::RobotWrapper(Basicbot *bot, Pathfinder *pf):m_bot(bot), pfp(pf), waitingForOrder(true)
{
    lastFacing = m_bot->facing;
    lastCoordinate = m_bot->lastReadCellQR;
}

void RobotWrapper::Tick()
{
    if (m_bot->currentInstruction == idle)
    {
        //Update location of pod while carrying
        if(m_bot->isCarrying){
            currentOrder->podPtr->location = std::pair<int,int>(m_bot->lastReadCellQR.x, m_bot->lastReadCellQR.y);
        }

        if(instructionQueue.empty())
        {
            waitingForOrder = true;
        }
        else
        {
            SendNextInstruction();
        }
    }
}

void RobotWrapper::ProcessNewOrder()
{
    waitingForOrder = false;

    int TC = pfp->em->tickCounter;

    Coordinate coordPod = Coordinate(currentOrder->podPtr->location.first, currentOrder->podPtr->location.second);
    Coordinate coordPick = Coordinate(currentOrder->pickStation->pickCoordinate.first, currentOrder->pickStation->pickCoordinate.second);
    Coordinate coordPodParkingSpot = Coordinate(currentOrder->podPtr->location.first, currentOrder->podPtr->location.second);

    Path pathToPickingStation;
    Path pathToPod;
    Path pathToPodParkingSpot;

    // Find path from bots last location to pod location
    pathToPod = pfp->FindPath(TC, lastCoordinate, coordPod, lastFacing, false);
    TC = pathToPod.arriveAtTick;
    TranslatePathToInstructions(pathToPod);

    // arrive at pod placement
    AddInstructionToQueue(pickuppod, 1);
    TC += 20;

    // Find path to picking station
    pathToPickingStation = pfp->FindPath(TC, coordPod, coordPick, lastFacing, true);
    TC = pathToPickingStation.arriveAtTick;
    TranslatePathToInstructions(pathToPickingStation);

     // Arrive at picking station. Waiting for x seconds.
    AddInstructionToQueue(_wait, 50);
    TC += 20;

    // pathfind back to pod original position. TODO: Changed later to find available spot
    pathToPodParkingSpot = pfp->FindPath(TC, coordPick, coordPodParkingSpot, lastFacing, true);
    TranslatePathToInstructions(pathToPodParkingSpot);
    TC = pathToPodParkingSpot.arriveAtTick;

    // put down pod
    AddInstructionToQueue(putdownpod, 1);
    TC += 20;

    //TODO: move out of the way. Maybe a go-home function if idle for too long.
    //lastTick = TC
}

void RobotWrapper::TranslatePathToInstructions(Path p)
{
    int counter = p.waypoints.size();
    if(counter==0){
        argos::LOGERR<<"can't translate empty path." << std::endl;
        return;}

    int diff = 0;

    for (int i = 0; i < counter; i++)
    {
        // Add wait-instruction by formula Coordinate(-1, ticksToWait)
        if(p.waypoints.front().x == -1){
            AddInstructionToQueue(_wait, p.waypoints.front().y);
            continue;
        }

        instruction n;
        direction f = GetFaceTowardsInstruction(p.waypoints.front(), lastCoordinate, lastFacing);
        switch (lastFacing)
        {
            case north :
                if (f==north){n=ignore;}
                else if(f==south){n=turn180;}
                else if(f==east){n=turnleft;}
                else if(f==west){n=turnright;}
                break;
            case south :
                if (f==north){n=turn180;}
                else if(f==south){n=ignore;}
                else if(f==east){n=turnright;}
                else if(f==west){n=turnleft;}
                break;
            case east :
                if (f==north){n=turnright;}
                else if(f==south){n=turnleft;}
                else if(f==east){n=ignore;}
                else if(f==west){n=turn180;}
                break;
            case west :
                if (f==north){n=turnleft;}
                else if(f==south){n=turnright;}
                else if(f==east){n=turn180;}
                else if(f==west){n=ignore;}
                break;
            default:
                break;
        }
        lastFacing = f;

        AddInstructionToQueue(n, 1);

        // how many cell to move forward
        if(lastCoordinate.x != p.waypoints.front().x){
            diff = abs(lastCoordinate.x - p.waypoints.front().x);}
        else{
            diff = abs(lastCoordinate.y - p.waypoints.front().y);
        }

        AddInstructionToQueue(moveforward, diff);

        lastCoordinate = p.waypoints.front();
        p.waypoints.pop();
    }
}

void RobotWrapper::SendNextInstruction()
{
    if(!instructionQueue.empty()){
        instruction nextInstruction = instructionQueue.front();
        instructionQueue.pop();

        switch (nextInstruction)
        {
        case moveforward:
            m_bot->cellsToMove = instructionsValuesQueue.front();
            instructionsValuesQueue.pop();
            m_bot->currentInstruction = moveforward;
            break;
        case turnleft:
            m_bot->currentInstruction = turnleft;
            break;
        case turnright:
            m_bot->currentInstruction = turnright;
            break;
        case turn180:
            m_bot->currentInstruction = turn180;
            break;
        case pickuppod:
            m_bot->currentInstruction = pickuppod;
            break;
        case putdownpod:
            m_bot->currentInstruction = putdownpod;
            break;
        case _wait:
            m_bot->ticksToWait = instructionsValuesQueue.front();
            instructionsValuesQueue.pop();
            m_bot->currentInstruction = _wait;
            break;

        default:
            break;
        }
    }
}

direction RobotWrapper::GetFaceTowardsInstruction(Coordinate coordToFace, Coordinate lastCoordinate, direction _lastFacing)
{
    direction nextFacing = _lastFacing; // return original facing if xdiff and ydiff are zero.

    int xdiff = lastCoordinate.x-coordToFace.x;
    int ydiff = lastCoordinate.y-coordToFace.y;

    if(xdiff != 0){
        nextFacing = (xdiff < 0) ? north : south;
    }
    else if (ydiff != 0){
        nextFacing = (ydiff < 0) ?  east : west;
    }

    return nextFacing;
}

void RobotWrapper::AddInstructionToQueue(instruction ins, int tiles = 1)
{
    if(ins == ignore){return;}

    instructionQueue.push(ins);
    if(ins == moveforward)
    {
        instructionsValuesQueue.push(tiles);
    }
    if(ins == _wait)
    {
        instructionsValuesQueue.push(tiles);
    }
};


#endif