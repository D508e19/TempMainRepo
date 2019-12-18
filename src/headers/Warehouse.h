#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "controllers/basicbot/basicbot.h"

class Warehouse
{
private:
    

    const int numberOfPickingStations = 3;
   
public:
    Warehouse();
    ~Warehouse();

    std::map<int, Basicbot*> bots;

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