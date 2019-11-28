#ifndef WAREHOUSE_H
#define WAREHOUSE_H

class Warehouse;

#include "src/orders/OrderManager.h"
#include "src/pods/PodManager.h"
#include "src/robots/RobotManager.h"

class Warehouse
{
private:
    OrderManager om;
    PodManager pm;
    RobotManager rm;

    bool distributed = false;

public:
    Warehouse();
    ~Warehouse();

    void SetupWarehouse(std::map<int, Basicbot *> botControllers);
    void Tick();
};

#endif