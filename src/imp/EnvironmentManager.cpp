#ifndef ENVIRONMENT_MANAGER_CPP
#define ENVIRONMENT_MANAGER_CPP

//#include <tuple>

#include "src/headers/EnvironmentManager.h"

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

	Coordinate t1 = Coordinate(1,5);
	Coordinate t2 = Coordinate(1,50);
	Coordinate t3 = Coordinate(-1,9);
	argos::LOG << IsValidCoordinate(t1) << std::endl;
	argos::LOG << IsValidCoordinate(t2) << std::endl;
	argos::LOG << IsValidCoordinate(t3) << std::endl;

}

void EnvironmentManager::Tick()
{
	tickCounter++;

	//argos::LOG << "Current tick: " << tickCounter << std::endl;
	//argos::LOG << "Current timeslot: " << currentTimeslots.front() << std::endl;

	if (tickCounter == currentTimeslots[1])
	{
		int nextTimeslot = currentTimeslots.back() + numberOfTicksPerTimeslot;
		
		// Update Reservations Table
		reservationsTable.erase(currentTimeslots.front());
		reservationsTable.insert(std::pair <int, std::vector <reservation>>(nextTimeslot, floorMap));

		currentTimeslots.erase(currentTimeslots.begin());
		currentTimeslots.push_back(nextTimeslot);
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

	if(startTick < currentTimeslots.front())//-numberOfTicksPerTimeslot)
	{
		// startTick is in the past
		return false;
	}

	//find timeslot
		

	//reservationsTable


	return false;
}

#endif
