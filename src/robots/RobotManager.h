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

    int robotCount = 0;

public:
    RobotManager();
    //RobotManager(std::map<int, Basicbot*>);
    ~RobotManager();

    RobotWrapper CreateRobotWrapper(Basicbot*);

    void SetupRobotManager(std::map<int, Basicbot*> botControllers);
    void Tick();
};
RobotManager::RobotManager(){};
RobotManager::~RobotManager(){};

void RobotManager::SetupRobotManager(std::map<int, Basicbot*> botControllers)
{
    for (int i=0; i<botControllers.size(); i++)
    {
        RobotWrapper rw = CreateRobotWrapper(botControllers[i]);
        Wrappers.insert(std::pair<int, RobotWrapper> (i, rw));
    }
};

void RobotManager::Tick()
{
    for (int i = 0; i < robotCount; i++)
    {
        Wrappers[i].Tick();
    }
};

RobotWrapper RobotManager::CreateRobotWrapper(Basicbot* b)
{
    RobotWrapper rw(b);
    robotCount++;
    return rw;
};

#endif
