#ifndef ENVIRONMENT_MANAGER_CPP
#define ENVIRONMENT_MANAGER_CPP

//#include <tuple>

//#include "src/headers/EnvironmentManager.h"

EnvironmentManager::EnvironmentManager(){}
EnvironmentManager::~EnvironmentManager(){}

void EnvironmentManager::SetupEnvirionmentManager()
{
    warehouseHeight = 10;
    warehouseLength = 10;

	numberOfTicksPerTimeslot = 20;
	timeslotsIntoTheFuture = 30;

	tickCounter = 0;
	
	// first floormap
	for (int h = 0; h < warehouseHeight; h++)
	{
		for (int l = 0; l < warehouseLength; l++)
		{
			floorMap.push_back(reservation(l,h,false));
		}
	}

	// add always blocked cells. like picking stations?
	// TODO

	// empty reservationsTable
	int timeslot = 0; 
	for (int i = 0; i < timeslotsIntoTheFuture; i++)
	{
		reservationsTable.insert(std::pair <int, std::vector <reservation>>(timeslot, floorMap));
		currentTimeslots.push_back(timeslot);
		timeslot += numberOfTicksPerTimeslot;
	}
}

void EnvironmentManager::Tick()
{
	tickCounter++;

	// Checking if first timeslot is in the past
	if (tickCounter >= currentTimeslots[1]) 
	{
		int nextTimeslot = currentTimeslots.back() + numberOfTicksPerTimeslot;
		
		// Update Reservations Table
		reservationsTable.erase(currentTimeslots.front());
		reservationsTable.insert(std::pair <int, std::vector <reservation>>(nextTimeslot, floorMap));

		currentTimeslots.erase(currentTimeslots.begin());
		currentTimeslots.push_back(nextTimeslot);
	}

	//TODO: delete. for testing
	if (!podParking.empty())
	{
		if(podParking[std::pair<int,int>(1,5)]){
			argos::LOG << "Pod for 1,4 is not null " << std::endl;
		}
		else
		{
			argos::LOG << "Pod for 1,4 is null " << std::endl;;
		}
	}
}

bool EnvironmentManager::IsValidCoordinate(Coordinate cand)
{
	return ((cand.x >= 0 && cand.x < warehouseLength) && (cand.y >= 0 && cand.y < warehouseHeight));
}

bool EnvironmentManager::ReserveCell(Coordinate cell, int startTick, int endTick)
{
	if(!IsValidCoordinate(cell))
	{
		// cell not in warehouse
		return false;
	}

	if(startTick > endTick)
	{
		// timespan illegal
		return false;
	}

	if(startTick < currentTimeslots.front())//-numberOfTicksPerTimeslot)
	{
		// startTick is in the past
		return false;
	}

	//find timeslot for startTick		
    //find timeslot for endTick	
	//calculate if any inbetween

	//find timeslots in reservationsTable
	//if already blocked return false
	//else block and return true 

	return false;
}
    
bool EnvironmentManager::ParkPod(Pod* pod)
{
	//TODO
	return false;
}

void EnvironmentManager::PlacePod(Pod* pod, Coordinate cord)
{
	podParking[std::pair<int, int>(cord.x, cord.y)] = pod;
}

#endif
