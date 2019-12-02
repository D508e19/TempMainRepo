#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "src/argos/controllers/basicbot/basicbot.h"

class Warehouse
{
private:
    std::map<int, Basicbot*> bots;

    bool distributed = false;

public:
    Warehouse();
    ~Warehouse();

    OrderManager om;
    PodManager pm;
    RobotManager rm;
    DataCollector dc;

    void SetupWarehouse(std::map<int, Basicbot*> botControllers);
    void Tick();

    void CollectData();
};

#endif