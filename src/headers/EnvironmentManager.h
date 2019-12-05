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
    int warehouseLength; //x = warehouseLength -1
    int warehouseHeight; //y = warehouseHeight -1
    
    int numberOfTicksPerTimeslot;
    int timeslotsIntoTheFuture;

    int tickCounter;

    std::map<cube, bool> floorMap;
    //std::map <int, std::vector <reservation>> reservationsTable;
    std::map <int, std::map <cube, bool>> reservationsTable;

    std::vector <int> currentTimeslots;
    
public:
    EnvironmentManager();
    ~EnvironmentManager();

    void SetupEnvirionmentManager();
    void Tick();

    void UpdateTimeslots(int tickCounter);

    bool ReserveCell(Coordinate cell, int startTick, int endTick);

    void AddParkingSpotsForPods(int numberOfPods, Pod* nullPod);
    bool ParkPod(Pod* pod);

    bool IsValidCoordinate(Coordinate cand);
    bool IsReserved(Coordinate cell, int tick);
    bool IsReserved(Coordinate cell, int startTick, int endTick);

    std::map <std::pair<int,int>, Pod*> podParking;
    std::vector <Coordinate> pickingStations;


};




#endif