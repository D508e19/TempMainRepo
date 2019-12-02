#ifndef WAREHOUSE_CPP
#define WAREHOUSE_CPP

#include "controllers/basicbot/basicbot.h"

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

#endif