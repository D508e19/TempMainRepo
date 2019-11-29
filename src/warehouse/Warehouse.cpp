#include "warehouse/Warehouse.h"

Warehouse::Warehouse(){};
Warehouse::~Warehouse(){};

void Warehouse::Tick()
{
    om.Tick();
    rm.Tick();
    pm.Tick();
};

void Warehouse::SetupWarehouse(std::map<int, Basicbot *> botControllers)
{
    srand(time(NULL)); // seed for rng
    // Andet setup ?
    om.SetupOrderManager(this);
    pm.SetupPodManager(this, 100);
    rm.SetupRobotManager(this, botControllers);
}
