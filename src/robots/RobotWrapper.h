#ifndef ROBOTWRAPPER_H
#define ROBOTWRAPPER_H

#include <vector> 
#include <queue>

#include "controllers/basicbot/basicbot.h"
#include "src/pathfinder/Pathfinder.h"
#include "src/datatypes/ds_instruction.h"
#include "src/datatypes/Path.h"

class RobotWrapper
{
private:
    std::queue<instruction> instructionQueue;
    std::queue<int> instructionsValuesQueue;

    Basicbot* m_bot;
    Pathfinder pf = Pathfinder();

    direction lastFacing;
    Coordinate lastCoordinate;

public:
    RobotWrapper();
    RobotWrapper(Basicbot *bot);
    ~RobotWrapper();

    void Tick();

    void TranslatePathToInstructions(Path p);
    void AddInstructionToQueue(instruction ins, int tiles);
    void SendNextInstruction();

    direction GetFaceTowardsInstruction(Coordinate wantsToFace, Coordinate current, direction lastFacing);
};

RobotWrapper::RobotWrapper(){};
RobotWrapper::~RobotWrapper(){};

RobotWrapper::RobotWrapper(Basicbot *bot):m_bot(bot)
{
    lastFacing = m_bot->facing;
    lastCoordinate = m_bot->lastReadCellQR;

    for (int i = 0; i < 5; i++)
    {
        TranslatePathToInstructions(pf.GetStupidPath(lastCoordinate, Coordinate(rand()%5,rand()%5)));
    }
    
};

void RobotWrapper::Tick()
{
    if (m_bot->currentInstruction == idle)
    { 
        /*
        if(instructionQueue.empty())
        {
            argos::LOG << "InstructionQueue empty. Generate new random path." << std::endl;
            // Add random path
            // TODO: Delete 
            TranslatePathToInstructions(pf.GetStupidPath(lastCoordinate, Coordinate(rand()%5,rand()%5)));
        }*/
        SendNextInstruction();
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
            AddInstructionToQueue(wait, p.waypoints.front().y);
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

        // Todo: change to ternary?
        if(lastCoordinate.x != p.waypoints.front().x){
            diff = abs(lastCoordinate.x - p.waypoints.front().x);}
        else{
            diff = abs(lastCoordinate.y - p.waypoints.front().y);
        }
        argos::LOG << "moving: "<< diff << std::endl;
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
        case wait:
            m_bot->ticksToWait = instructionsValuesQueue.front();
            instructionsValuesQueue.pop();
            m_bot->currentInstruction = wait;
        
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
    if(ins == wait)
    {
        instructionsValuesQueue.push(tiles);
    }
};


#endif