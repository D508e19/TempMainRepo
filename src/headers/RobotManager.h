#ifndef ROBOTMANAGER_H
#define ROBOTMANAGER_H

class RobotManager
{
private:
    std::map<int, RobotWrapper> Wrappers;
    int robotCount = 0;

    Warehouse* wh;

public:
    RobotManager();
    ~RobotManager();

    RobotWrapper CreateRobotWrapper(Basicbot*);

    void SetupRobotManager(Warehouse* _wh, std::map<int, Basicbot*> botControllers);
    void Tick();
};

#endif