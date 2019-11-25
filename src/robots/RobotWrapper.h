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

};

void RobotWrapper::Tick()
{
    std::mutex mtx;

    if(instructionQueue.empty()&&m_bot->isBusy==false)
    {
        mtx.lock();
        TranslatePathToInstructions(pf.GetStupidPath(lastCoordinate, Coordinate(5,5)));
        mtx.unlock();
    }
    if (m_bot->currentInstruction == idle)
    { 
        SendNextInstruction();
    }
}

void RobotWrapper::TranslatePathToInstructions(Path p)
{
    //Coordinate lastCoordinate = m_bot->lastReadCellQR;
    int counter = p.waypoints.size();
    int diff = 0;

    for (int i = 0; i < counter; i++)
    {
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
        //std::cout << "Sending ins to face: " << f << std::endl;
        AddInstructionToQueue(n, 1);

        //change to ternary?
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

direction RobotWrapper::GetFaceTowardsInstruction(Coordinate cToFace, Coordinate lastCoordinate, direction _lastFacing)
{
    //std::cout << "In cell: " << lastCoordinate.x << ","<< lastCoordinate.y<< std::endl;
    //std::cout << "Last faced: " << _lastFacing << std::endl;
    //std::cout << "Want to face: " << cToFace.x << ","<< cToFace.y<< std::endl;
    //instruction i;
    direction nextFacing = _lastFacing;
    //Coordinate c = lastCoordinate;

    int xdiff = lastCoordinate.x-cToFace.x;
    int ydiff = lastCoordinate.y-cToFace.y;

    if(xdiff!=0){
        nextFacing = (xdiff < 0) ? north : south;
    }
    else{
        nextFacing = (ydiff < 0) ?  east : west; 
    }
    //std::cout << "Gonna face: " << nextFacing << std::endl;
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
        
        default:
            break;
        }
    }
}

void RobotWrapper::AddInstructionToQueue(instruction ins, int tiles = 1)
{
    if(ins == ignore){return;}

    //std::cout << "queuing ins: " << ins << std::endl;
    instructionQueue.push(ins);
    if(ins == moveforward)
    {
        instructionsValuesQueue.push(tiles);
    }
};


#endif