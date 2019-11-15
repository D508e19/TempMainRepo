#ifndef ROBOTWRAPPER_H
#define ROBOTWRAPPER_H

class robotWrapper
{
private:
    //instructionQueue[]
    void MoveForward(int cells);
    void TurnLeft();
    void TurnRight();
    void Turn180();
    void PickupPod();
    void PutDownPOd();

public:
    robotWrapper();
    ~robotWrapper();


};

robotWrapper::robotWrapper(){}

robotWrapper::~robotWrapper(){}



#endif