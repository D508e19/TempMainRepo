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
    while (!ordersToBeProcessed.empty())
	{
		Order* nextOrder = ordersToBeProcessed.front();
        // TODO:
        // pick robot
        // get path
        // send path to wrapper
        // ???
        // profit

		wh->om.ordersOngoing.push(nextOrder);
		ordersToBeProcessed.pop();
	}

    for (int i = 0; i < robotCount; i++)
    {
        Wrappers[i].Tick();
    }
}

RobotWrapper RobotManager::CreateRobotWrapper(Basicbot* b)
{
    RobotWrapper rw(b, environmentManager);
    robotCount++;
    return rw;
}

#endif