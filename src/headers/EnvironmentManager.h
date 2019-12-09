#ifndef ENVIRONMENT_MANAGER_H
#define ENVIRONMENT_MANAGER_H

#include <map>
#include <vector>

#include "src/headers/Coordinate.h"
#include "src/headers/Pod.h"

typedef std::tuple<int, int, bool> reservation;
typedef std::pair<int,int> cube;

class EnvironmentManager
{
private:
    int numberOfTicksPerTimeslot;
    int timeslotsIntoTheFuture;


    std::map<cube, bool> floorMap;
    //std::map <int, std::vector <reservation>> reservationsTable;
    std::map <int, std::map <cube, bool>> reservationsTable;

    std::vector <int> currentTimeslots;

    Warehouse *wh;
    
public:
    EnvironmentManager();
    ~EnvironmentManager();

    void SetupEnvirionmentManager(Warehouse * _wh);
    void Tick();

    void UpdateTimeslots(int tickCounter);

    bool ReserveCell(Coordinate cell, int startTick, int endTick);

    bool IsValidCoordinate(Coordinate cand);
    bool IsReserved(Coordinate cell, int tick);
    bool IsReserved(Coordinate cell, int startTick, int endTick);

    
    int tickCounter;

    std::map <std::pair<int,int>, Pod*> podParking;
    std::vector <Coordinate> pickingStations;

    int warehouseLength; //x = warehouseLength -1
    int warehouseHeight; //y = warehouseHeight -1

    void PlacePod(Pod* pod, Coordinate cord);

    std::pair<int, int> FindPodLocation(Pod* pod);

    int GetPodID(std::pair<int, int> coordinate);

    bool PickUpPod(int podID, std::pair<int,int> coordinate);
    bool PutDownPod(int podID, std::pair<int,int> coordinate);
};




#endif