#ifndef WAREHOUSE_H
#define WAREHOUSE_H

class Warehouse;

#include "src/orders/OrderManager.h"
#include "src/pods/PodManager.h"
#include "src/robots/RobotManager.h"
#include "src/data/DataCollector.h"

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

Warehouse::Warehouse(){};
Warehouse::~Warehouse(){};

void Warehouse::Tick()
{
    om.Tick();
    rm.Tick();
    pm.Tick();  
};

void Warehouse::SetupWarehouse(std::map<int, Basicbot*> botControllers)
{
    bots = botControllers;
    srand (time(NULL));	// seed for rng
    // andet setup ?
    om.SetupOrderManager(this); 
    pm.SetupPodManager(this, 100);
    rm.SetupRobotManager(this, botControllers);
}

void Warehouse::CollectData()
{
    dc.CollectData(bots);
}

void Warehouse::AddOrderToProcessQueue(Order* order)
{
    argos::LOG << order->getOrderID() << std::endl;
    orderQueue.push(order);
};



#endif