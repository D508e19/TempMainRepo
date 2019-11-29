#ifndef ROBOTMANAGER_CPP
#define ROBOTMANAGER_CPP

RobotManager::RobotManager(){};
RobotManager::~RobotManager(){};

void RobotManager::SetupRobotManager(Warehouse* _wh, std::map<int, Basicbot*> botControllers)
{
    wh = _wh;

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