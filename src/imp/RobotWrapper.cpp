#ifndef ROBOTWRAPPER_CPP
#define ROBOTWRAPPER_CPP

#include "controllers/basicbot/basicbot.h"

RobotWrapper::RobotWrapper(){};
RobotWrapper::~RobotWrapper(){};

RobotWrapper::RobotWrapper(Basicbot *bot):m_bot(bot)
{
    lastFacing = m_bot->facing; // TODO: check if working. seems like not.
    lastCoordinate = m_bot->lastReadCellQR; // TODO: check if working. seems like not.
}

void RobotWrapper::Tick()
{
    if (m_bot->currentInstruction == idle)
    {    
        if(instructionQueue.empty())
        {
            if(!waitingForOrder){
                // If bot is idle, the instructionQueue is empty and bot isn't waitingForOrder 
                //it means that it has received a new order

                //cheat - These are to control which coords the bots gets
                currentOrder->podLocation = cube(rand()%10,rand()%10);
                currentOrder->pickStationLocation = cube(rand()%10,rand()%10);

                currentOrder->podLocation = cube(2,3);
                currentOrder->pickStationLocation = cube(4,2);
                ///////

                // Find path from bots last location to pod location
                Coordinate podCoord = Coordinate(currentOrder->podLocation.first,currentOrder->podLocation.second);
                Path pathToPod = pf.FindPath(lastCoordinate, podCoord, lastFacing, isCarrying);
                TranslatePathToInstructions(pathToPod);

                // arrive at pod placement
                // TODO: check if pod is actually here
                AddInstructionToQueue(pickuppod, 1);
                // TODO: isCarrying. Who changes this value? 

                // Find path to picking station
                Coordinate pickCoord = Coordinate(currentOrder->pickStationLocation.first,currentOrder->pickStationLocation.second);
                Path pathToPickstation = pf.FindPath(lastCoordinate, pickCoord, lastFacing, isCarrying);
                TranslatePathToInstructions(pathToPickstation);

                // Arrive at picking station. Waiting for 5 seconds. TODO: ticksToPicks should be moved out to a variable.
                AddInstructionToQueue(_wait, 50);


                // pathfind back to pod original position. Changed later to find avalibale spot
                Path pathToPodSpot = pf.FindPath(lastCoordinate, podCoord, lastFacing, isCarrying);
                TranslatePathToInstructions(pathToPod);

                // put down pod
                AddInstructionToQueue(putdownpod, 1);
                // TODO: isCarrying. Who changes this value?

                //TODO: move out of the way. Maybe a go-home function if idle for too long.
            }
            else 
            {
                waitingForOrder = true;
            }
        } 
        SendNextInstruction(); // TODO: refactor to over new-order-received, since it is the most common endpoint.
    }
}

void RobotWrapper::TranslatePathToInstructions(Path p)
{
    int counter = p.waypoints.size();
    int diff = 0;

    for (int i = 0; i < counter; i++)
    {
        // wait instruction is added TODO comment more
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
        // Todo: change to ternary?
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

direction RobotWrapper::GetFaceTowardsInstruction(Coordinate coordToFace, Coordinate lastCoordinate, direction _lastFacing)
{
    direction nextFacing = _lastFacing;

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
        
        default:
            break;
        }
    }
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