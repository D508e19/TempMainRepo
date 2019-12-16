#ifndef ENVIRONMENT_MANAGER_H
#define ENVIRONMENT_MANAGER_H

#include <map>
#include <vector>

#include "src/headers/Coordinate.h"
#include "src/headers/Pod.h"

typedef std::tuple<Coordinate, int, int> reservation;
typedef std::pair<int,int> cube;

class EnvironmentManager
{
private:
    Warehouse *wh;

    std::map<cube, bool> floorMap;
    std::map <int, std::map <cube, bool>> reservationsTable;
    std::vector <int> currentTimeslots;
    
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
    int GetTimeslot(int tick);

    int GetPodID(std::pair<int, int> coordinate);
    bool PickUpPod(int podID, std::pair<int,int> coordinate);
    bool PutDownPod(int podID, std::pair<int,int> coordinate);
    void PlacePod(Pod* pod, Coordinate cord);
    std::pair<int, int> FindPodLocation(Pod* pod);

    int tickCounter;
    int numberOfTicksPerTimeslot;
    int timeslotsIntoTheFuture;

    int warehouseLength; 
    int warehouseHeight; 

    std::map <std::pair<int,int>, Pod*> podParking;
    std::vector <Coordinate> pickingStations;
};


#endif