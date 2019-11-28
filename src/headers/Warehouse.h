#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "controllers/basicbot/basicbot.h"


class Warehouse
{
private:
    OrderManager om;
    PodManager pm;
    RobotManager rm;
    DataCollector dc;

    std::map<int, Basicbot*> bots;

    std::queue<Order*> orderQueue;

    bool distributed = false;

public:
    Warehouse();
    ~Warehouse();

    void SetupWarehouse(std::map<int, Basicbot*> botControllers);
    void Tick();    

    void AddOrderToProcessQueue(Order* order);

    void CollectData(); 
};

#endif