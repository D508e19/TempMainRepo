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

public:
    Warehouse();
    ~Warehouse();

    void SetupWarehouse(std::map<int, Basicbot*> botControllers);
    void Tick();    
};

Warehouse::Warehouse(){};
Warehouse::~Warehouse(){};

void Warehouse::Tick() // skifte navn til Tick eller step?
{
    om.Tick();
    rm.Tick();
    pm.Tick();  
};

void Warehouse::SetupWarehouse(std::map<int, Basicbot*> botControllers)
{
    srand (time(NULL));	// seed for rng
    // andet setup ?
    rm.SetupRobotManager(botControllers);
    pm.SetupPodManager(100);
    om.SetupOrderManager(pm.GetPodCount()); 
}


#endif