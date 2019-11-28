#ifndef WAREHOUSE_H
#define WAREHOUSE_H

class Warehouse;

#include "src/orders/OrderManager.h"
#include "src/pods/PodManager.h"
#include "src/robots/RobotManager.h"
#include "src/networking/Networking.h"

class Warehouse
{
private:
    OrderManager om;
    PodManager pm;
    RobotManager rm;
    Networking net;

    bool distributed = false;

public:
    Warehouse();
    ~Warehouse();

    void SetupWarehouse(std::map<int, Basicbot*> botControllers);
    void Tick();    
};

Warehouse::Warehouse(){};
Warehouse::~Warehouse(){};

void Warehouse::Tick()
{
    net.Tick();
    om.Tick();
    rm.Tick();
    pm.Tick();  
};

void Warehouse::SetupWarehouse(std::map<int, Basicbot*> botControllers)
{
    srand (time(NULL));	// seed for rng
    // andet setup ?
    om.SetupOrderManager(this); 
    pm.SetupPodManager(this, 100);
    rm.SetupRobotManager(this, botControllers);

    net.Connect();
}


#endif