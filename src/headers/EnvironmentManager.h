#ifndef ENVIRONMENT_MANAGER_H
#define ENVIRONMENT_MANAGER_H

#include <map>
#include <vector>

#include "src/headers/Coordinate.h"
#include "src/headers/Pod.h"

typedef std::tuple<int, int, bool> reservation;

class EnvironmentManager
{
private:
    int warehouseLength; //x = warehouseLength -1
    int warehouseHeight; //y = warehouseHeight -1
    
    int numberOfTicksPerTimeslot;
    int timeslotsIntoTheFuture;

    int tickCounter;

    std::vector <reservation> floorMap;
    std::map <int, std::vector <reservation>> reservationsTable;

    std::vector <int> currentTimeslots;
    
public:
    EnvironmentManager();
    ~EnvironmentManager();

    void SetupEnvirionmentManager();
    void Tick();

    bool IsValidCoordinate(Coordinate cand);
    bool ReserveCell(Coordinate cell, int startTick, int endTick);

    std::map <Coordinate, Pod*> podParking;
    std::vector <Coordinate> pickingStations;


};




#endif