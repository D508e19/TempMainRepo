#ifndef WAREHOUSE_H
#define WAREHOUSE_H

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

    int x =5;

public:
    Warehouse();
    ~Warehouse();

    void SetupWarehouse(std::map<int, Basicbot*> botControllers);
    void RunWarehouse();    
};

Warehouse::Warehouse(){};
Warehouse::~Warehouse(){};

void Warehouse::RunWarehouse() // skifte navn til Tick eller step?
{
    om.RunOrderManager();
    rm.RunRobotManager();
    pm.RunPodManager();  
};

void Warehouse::SetupWarehouse(std::map<int, Basicbot*> botControllers)
{
    // andet setup ?
    rm.SetupRobotManager(botControllers);
    pm.SetupPodManager(100);
    om.SetupOrderManager(pm.GetPodCount()); 
}


#endif