#ifndef ROBOTMANAGER_CPP
#define ROBOTMANAGER_CPP

RobotManager::RobotManager(){};
RobotManager::~RobotManager(){};

void RobotManager::SetupRobotManager(Warehouse* _wh, std::map<int, Basicbot*> botControllers, EnvironmentManager* _environmentManager)
{
    environmentManager = _environmentManager;
    wh = _wh;

    for (int i=0; i<botControllers.size(); i++)
    {
        RobotWrapper rw = CreateRobotWrapper(botControllers[i]);
        Wrappers.insert(std::pair<int, RobotWrapper> (i, rw));
    }
}

void RobotManager::Tick()
{
    for (int i = 0; i < robotCount; i++)
    {
        if(Wrappers[i].waitingForOrder && !ordersToBeProcessed.empty())
        {
            Wrappers[i].currentOrder = ordersToBeProcessed.front();
            ordersToBeProcessed.pop();
            Wrappers[i].waitingForOrder = false;
        }

        Wrappers[i].Tick();
    }
}

RobotWrapper RobotManager::CreateRobotWrapper(Basicbot* b)
{
    RobotWrapper rw(b, wh->pf, environmentManager);
    robotCount++;
    return rw;
}

#endif