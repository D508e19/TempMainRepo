#ifndef ROBOTWRAPPER_H
#define ROBOTWRAPPER_H

#include <vector> 
#include <queue>

#include <controllers/basicbot/basicbot.h>

class robotWrapper
{
private:
    std::queue<instruction> instructionQueue;
    std::queue<int> instructionsValuesQueue;

    Basicbot &m_bot;

    void MoveForward(int cells);
    void TurnLeft();
    void TurnRight();
    void Turn180();
    void PickupPod();
    void PutDownPOd();

    void RunNextInstruction();

public:
    robotWrapper(Basicbot &bot);
    ~robotWrapper();
};

enum instruction{moveforward, turnleft, turnright, turn180, pickuppod, putdownpod};

robotWrapper::robotWrapper(Basicbot &bot):m_bot(bot){}

robotWrapper::~robotWrapper(){}

void robotWrapper::RunNextInstruction()
{
    if(!instructionQueue.empty){
        switch (instructionQueue.pop)
        {
        case moveforward:
            MoveForward(instructionsValuesQueue.pop);
            break;
        case turnleft:
            TurnLeft();
            break;
        case turnright:
            TurnRight();
            break;
        case turn180:
            Turn180();
            break;
        case pickuppod:
            PickupPod();
            break;
        case putdownpod:
            PutDownPOd();
            break;
        
        default:
            break;
        }
    }
}



#endif