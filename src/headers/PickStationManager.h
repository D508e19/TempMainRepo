#ifndef PICKSTATIONMANAGER_H
#define PICKSTATIONMANAGER_h

#include <stdlib.h>
#include <map>

class PickStationManager
{
private:
    
    Warehouse* wh;

    std::map<int, PickStation*> stations;

    void GeneratePickStations(int startzone_width, int arena_height, int numberOfPickingStations);

public:
    PickStationManager();
    ~PickStationManager();

    void SetupPickStationManager(Warehouse* _wh, int numberOfPickingStations);

    void Tick();

    void AddPickingStation(int id, std::pair<int,int> coordinate);

    PickStation* GetPickStationForOrder();
};

#endif