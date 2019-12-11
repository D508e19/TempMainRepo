#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "controllers/basicbot/basicbot.h"

class Warehouse
{
private:
    std::map<int, Basicbot*> bots;

    const int numberOfPickingStations = 2;
   
public:
    Warehouse();
    ~Warehouse();

    EnvironmentManager* em;
    OrderManager om;
    PickStationManager* psm;
    PodManager pm;
    RobotManager rm;
    DataCollector dc;
    Pathfinder* pf; 

    void SetupWarehouse(std::map<int, Basicbot*> botControllers);
    void Tick();    

    void CollectData(); 
};

#endif