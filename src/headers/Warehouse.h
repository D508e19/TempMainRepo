#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "src/argos/controllers/basicbot/basicbot.h"

class Warehouse
{
private:
    std::map<int, Basicbot *> bots;

public:
    Warehouse();
    ~Warehouse();

    EnvironmentManager *em;
    OrderManager om;
    PodManager pm;
    RobotManager rm;
    DataCollector dc;
    Pathfinder *pf;

    void SetupWarehouse(std::map<int, Basicbot *> botControllers);
    void Tick();

    void CollectData();
};

#endif