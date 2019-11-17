#ifndef ROBOTWRAPPER_H
#define ROBOTWRAPPER_H

#include <vector> 
#include <queue>

#include "controllers/basicbot/basicbot.h"
#include "src/customDataStructures.h"

class RobotWrapper
{
private:
    std::queue<instruction> instructionQueue;
    std::queue<int> instructionsValuesQueue;

    //Basicbot::Basicbot* m_bot;
    Basicbot* m_bot;

public:
    RobotWrapper();
    RobotWrapper(Basicbot *bot);
    ~RobotWrapper();

    void RunRobotWrapper();

    void AddInstructionToQueue(instruction ins, int tiles);
    void SendNextInstruction();
};

RobotWrapper::RobotWrapper(){};
RobotWrapper::~RobotWrapper(){};

RobotWrapper::RobotWrapper(Basicbot *bot):m_bot(bot)
{   
    //temp instruksgenerator 
    for (int i = 0; i < 500; i++)
    {
        int j = rand() % 4;
        switch (j)
        {
        case 1:
            AddInstructionToQueue(turnleft, 1);
            break;
        case 2:
            AddInstructionToQueue(turnright, 1);
            break;
        case 3:
            AddInstructionToQueue(moveforward, rand()%5);
        default:
            break;
        }
    }
};

void RobotWrapper::RunRobotWrapper()
{
    if (m_bot->currentInstruction == idle)
    {
        SendNextInstruction();
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
        
        default:
            break;
        }
    }
}

void RobotWrapper::AddInstructionToQueue(instruction ins, int tiles = 1)
{
    instructionQueue.push(ins);
    if(ins == moveforward)
    {
        instructionsValuesQueue.push(tiles);
    }
};


#endif