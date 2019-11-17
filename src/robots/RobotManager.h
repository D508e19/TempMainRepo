#ifndef ROBOTMANAGER_H
#define ROBOTMANAGER_H

#include <list>
#include <map>

#include "RobotWrapper.h"
#include "src/robots/RobotWrapper.h"
#include "controllers/basicbot/basicbot.h"

class RobotManager
{
private:
    std::map<int, RobotWrapper> Wrappers;

public:
    RobotManager();
    //RobotManager(std::map<int, Basicbot*>);
    ~RobotManager();

    RobotWrapper CreateRobotWrapper(Basicbot*);

    void SetupRobotManager(std::map<int, Basicbot*> botControllers);
    void RunRobotManager();
};
RobotManager::RobotManager(){};
RobotManager::~RobotManager(){};

RobotWrapper RobotManager::CreateRobotWrapper(Basicbot* b)
{
    RobotWrapper rw(b);
    return rw;
};

void RobotManager::SetupRobotManager(std::map<int, Basicbot*> botControllers)
{
    /*
    // for hver controller: lav en wrpper : læg dem 
    int numberOfBots = botControllers.size();
    
    for (int i=0; i<numberOfBots; i++)
    {
        RobotWrapper rw(botControllers[i]);
        //#rw = CreateRobotWrapper(botControllers[i]);

        Wrappers.insert(std::pair<int, RobotWrapper> (i, rw));
    }
    */
};

void RobotManager::RunRobotManager()
{

};

#endif
