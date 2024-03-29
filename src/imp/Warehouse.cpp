#ifndef WAREHOUSE_CPP
#define WAREHOUSE_CPP

#include "controllers/basicbot/basicbot.h"

Warehouse::Warehouse(){};
Warehouse::~Warehouse(){};

void Warehouse::Tick()
{
    em->Tick();
    om.Tick();
    psm->Tick();
    pm.Tick();  
    rm.Tick();
};

void Warehouse::SetupWarehouse(std::map<int, Basicbot*> botControllers)
{
    bots = botControllers;
    srand (time(NULL));	// seed for rng

    em = new EnvironmentManager();
    em->SetupEnvirionmentManager(this);

    pf = new Pathfinder(em);

    om.SetupOrderManager(this);
    psm = new PickStationManager();
    psm->SetupPickStationManager(this, numberOfPickingStations);
    pm.SetupPodManager(this);
    rm.SetupRobotManager(this, botControllers);
}

void Warehouse::CollectData()
{
    dc.CollectData(this);
}

#endif