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
			floorMap[std::pair<int,int>(l,h)] = false;
		}
	}

	// add always blocked cells. like picking stations?
	// TODO

	// empty reservationsTable
	int timeslot = 0; 
	for (int i = 0; i < timeslotsIntoTheFuture; i++)
	{
		reservationsTable[timeslot] = floorMap;
		currentTimeslots.push_back(timeslot);
		timeslot += numberOfTicksPerTimeslot;
	}
}

void EnvironmentManager::Tick()
{
	tickCounter++;

	// Checking if first timeslot is in the past
	UpdateTimeslots(tickCounter);

	//IsReserved(Coordinate(1,1), 45);
	//ReserveCell(Coordinate(1,1), 44, 205);
	//ReserveCell(Coordinate(1,1), 4, 25);
	//ReserveCell(Coordinate(1,1), 144, 50);

	//TODO: delete. for testing
	/*if (!podParking.empty())
	{
		if(podParking[std::pair<int,int>(1,5)]){
			argos::LOG << "Pod for 1,4 is not null " << std::endl;
		}
		else
		{
			argos::LOG << "Pod for 1,4 is null " << std::endl;;
		}
	}*/
}

void EnvironmentManager::UpdateTimeslots(int tickCounter)
{
	if (tickCounter >= currentTimeslots[1]) 
	{
		int nextTimeslot = currentTimeslots.back() + numberOfTicksPerTimeslot;
		
		// Update Reservations Table
		reservationsTable.erase(currentTimeslots.front());
		reservationsTable[nextTimeslot] = floorMap;

		currentTimeslots.erase(currentTimeslots.begin());
		currentTimeslots.push_back(nextTimeslot);
	}
}

bool EnvironmentManager::IsValidCoordinate(Coordinate cand)
{
	return ((cand.x >= 0 && cand.x < warehouseLength) && (cand.y >= 0 && cand.y < warehouseHeight));
}

bool EnvironmentManager::IsReserved(Coordinate cell, int tick)
{
	int timeslot;
		for (int i = currentTimeslots[0]; i < timeslotsIntoTheFuture; i++)
	{
		if (tick < currentTimeslots[i+1]){
			timeslot = currentTimeslots[i];
			break;
		}
	}
	bool ans = (reservationsTable[timeslot][std::pair<int,int>(cell.x,cell.y)]);
	//argos::LOG << cell.x << "," << cell.y << "IsReserved: "<< ans << std::endl;
	return ans;
}

bool EnvironmentManager::IsReserved(Coordinate cell, int startTick, int endTick)
{
	// get all timeslots between startTick and endTick
	// call IsReserved for all

	int startTimeslot; 
	for (int i = currentTimeslots[0]; i < timeslotsIntoTheFuture; i++)
	{
		if (startTick < currentTimeslots[i+1]){
			startTimeslot = currentTimeslots[i];
			break;
		}
	}
	//argos::LOG << "startTick:" << startTick << " . Is in timeslot: "<< startTimeslot << std::endl;
	
    //find timeslot for endTick	
	int endTimeslot; 
	for (int i = currentTimeslots[0]; i < timeslotsIntoTheFuture; i++)
	{
		if (endTick < currentTimeslots[i+1]){
			endTimeslot = currentTimeslots[i];
			break;
		}
	}
	//argos::LOG << "endTick:" << endTick << " . Is in timeslot: "<< endTimeslot << std::endl;

	//put start, end and all inbetween in a queue
	int nextTimeslotToCheck = startTimeslot;
	std::queue <int> timeslotsToCheck;

	while (nextTimeslotToCheck <= endTimeslot)
	{
		timeslotsToCheck.push(nextTimeslotToCheck);
		nextTimeslotToCheck += numberOfTicksPerTimeslot;
	}

	bool ans = false;
	while (!timeslotsToCheck.empty()){
		if(IsReserved(cell, timeslotsToCheck.front()))
			{ans=true;}
		timeslotsToCheck.pop();
	}
	return ans;
}


bool EnvironmentManager::ReserveCell(Coordinate cell, int startTick, int endTick)
{
	if(!IsValidCoordinate(cell))
	{
		argos::LOG << "ERROR: Cell: " << cell.x << "," << cell.y << " is not in warehouse."<< std::endl;
		return false;
	}

	if(startTick > endTick)
	{
		argos::LOG << "ERROR: Endtick: "<< endTick <<" is before startTick: " << startTick  << std::endl; 
		return false;
	}

	if(startTick < currentTimeslots.front())
	{
		argos::LOG << "ERROR: startTick: " << startTick  <<" is in the past." << std::endl; 
		return false;
	}

	//TODO: test too far into the future

	//TODO: move into function FindTimeslot(int tick)
	//find timeslot for startTick	
	int startTimeslot; 
	for (int i = currentTimeslots[0]; i < timeslotsIntoTheFuture; i++)
	{
		if (startTick < currentTimeslots[i+1]){
			startTimeslot = currentTimeslots[i];
			break;
		}
	}
	argos::LOG << "startTick:" << startTick << " . Is in timeslot: "<< startTimeslot << std::endl;
	
    //find timeslot for endTick	
	int endTimeslot; 
	for (int i = currentTimeslots[0]; i < timeslotsIntoTheFuture; i++)
	{
		if (endTick < currentTimeslots[i+1]){
			endTimeslot = currentTimeslots[i];
			break;
		}
	}
	argos::LOG << "endTick:" << endTick << " . Is in timeslot: "<< endTimeslot << std::endl; 

	//put start, end and all inbetween in a queue
	int nextTimeslotToReserve = startTimeslot;
	std::queue <int> timeslotsToReserve;

	while (nextTimeslotToReserve <= endTimeslot)
	{
		timeslotsToReserve.push(nextTimeslotToReserve);
		nextTimeslotToReserve += numberOfTicksPerTimeslot;
	}
	
	/* TODO:: delete
	std::queue<int> testQueue = timeslotsToReserve;
	argos::LOG << "Reserve timeslots: " ;
	while(!testQueue.empty())
	{
		argos::LOG << testQueue.front() << ", ";
		testQueue.pop();
	}
	argos::LOG << std::endl; */


	//todo check all cubes before reserve

	while (!timeslotsToReserve.empty())
	{
		if (reservationsTable[timeslotsToReserve.front()][std::pair<int,int>(cell.x,cell.y)])
		{
			argos::LOGERR << "ERROR: Timeslot already reserved. This should be checked before calling ReserveCell" << std::endl;
			return false;
		}
		reservationsTable[timeslotsToReserve.front()][std::pair<int,int>(cell.x,cell.y)] = true;
		argos::LOG << "Qube: "<< cell.x << ","<<cell.y<< " in timeslot:" <<timeslotsToReserve.front() <<  " is reserved" << std::endl;
		timeslotsToReserve.pop();
	}

	return true;
}

void EnvironmentManager::AddParkingSpotsForPods(int numberOfPods, Pod* nullPod)
{
	// TODO: hardcoded podparking. Should be changed.
	podParking[std::pair<int,int>(1,4)] = NULL;
	podParking[std::pair<int,int>(1,5)] = nullPod;
	podParking[std::pair<int,int>(1,6)] = nullPod;
	podParking[std::pair<int,int>(1,7)] = nullPod;
	podParking[std::pair<int,int>(2,4)] = nullPod;
	podParking[std::pair<int,int>(2,5)] = nullPod;
	podParking[std::pair<int,int>(2,6)] = nullPod;
	podParking[std::pair<int,int>(2,7)] = nullPod;

}
    
bool EnvironmentManager::ParkPod(Pod* pod)
{
	//TODO
	return false;
}

#endif
