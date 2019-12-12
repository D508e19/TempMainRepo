#ifndef PICKSTATIONMANAGER_CPP
#define PICKSTATIONMANAGER_CPP

#include <stdlib.h>
#include <queue>

PickStationManager::PickStationManager(){}
PickStationManager::~PickStationManager(){}

void PickStationManager::SetupPickStationManager(Warehouse* _wh, int numberOfPickingStations)
{
    wh = _wh;
    GeneratePickStations(wh->pm.layout_startzone_width, wh->em->warehouseHeight, numberOfPickingStations);
}

void PickStationManager::Tick()
{
    for(auto stationPair : stations)
    {
        stationPair.second->Tick();
    }
}

void PickStationManager::GeneratePickStations(int startzone_width, int arena_height, int numberOfPickingStations)
{
    if(startzone_width == 0)
    {
        argos::LOGERR << "PickStationManager: Starting zone with is 0! No picking stations was created!" << std::endl;
        return;
    }

    if(arena_height < numberOfPickingStations)
    {
        argos::LOGERR << "PickStationManager: Arena height is less then the desired number of picking stations! No picking stations was created!" << std::endl;
        return;
    }
        
    int slot_height = arena_height / numberOfPickingStations;
    for(int i = 0; i < numberOfPickingStations; i++)
    {
        int y = slot_height * i + (slot_height / 2);
        AddPickingStation(i, std::pair<int,int>(0, y));
    }
}

void PickStationManager::AddPickingStation(int id, std::pair<int,int> coordinate)
{
    PickStation* newStation = new PickStation();
    newStation->SetupPickStation(id, coordinate, wh);
    stations[id] = newStation;
}

PickStation* PickStationManager::GetPickStationForOrder()
{   
    //TODO Could be replaced with logic to return the stations with the least amount of orders
    // Currently it picks a station at random
    return stations[floor(rand() % stations.size())]; 
}

#endif