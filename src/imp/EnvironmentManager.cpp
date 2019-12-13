#ifndef ENVIRONMENT_MANAGER_CPP
#define ENVIRONMENT_MANAGER_CPP

#include <map>

EnvironmentManager::EnvironmentManager(){}
EnvironmentManager::~EnvironmentManager(){}

void EnvironmentManager::SetupEnvirionmentManager(Warehouse * _wh)
{
	wh = _wh;

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
	UpdateTimeslots(tickCounter);
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
	return ans;
}

bool EnvironmentManager::IsReserved(Coordinate cell, int startTick, int endTick)
{
	int startTimeslot; 
	for (int i = currentTimeslots[0]; i < timeslotsIntoTheFuture; i++)
	{
		if (startTick < currentTimeslots[i+1]){
			startTimeslot = currentTimeslots[i];
			break;
		}
	}
	
    //find timeslot for endTick	
	int endTimeslot; 
	for (int i = currentTimeslots[0]; i < timeslotsIntoTheFuture; i++)
	{
		if (endTick < currentTimeslots[i+1]){
			endTimeslot = currentTimeslots[i];
			break;
		}
	}

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
		argos::LOGERR << "ERROR: Cell: " << cell.x << "," << cell.y << " is not in warehouse."<< std::endl;
		return false;
	}

	if(startTick > endTick)
	{
		argos::LOGERR << "ERROR: Endtick: "<< endTick <<" is before startTick: " << startTick  << std::endl; 
		return false;
	}

	if(startTick < currentTimeslots.front())
	{
		argos::LOGERR << "ERROR: startTick: " << startTick  <<" is in the past." << std::endl; 
		return false;
	}

	//find timeslot for startTick	
	int startTimeslot = GetTimeslot(startTick);

    //find timeslot for endTick	
	int endTimeslot = GetTimeslot(endTick); 

	//put start, end and all inbetween in a queue
	int nextTimeslotToReserve = startTimeslot;
	std::queue <int> timeslotsToReserve;

	while (nextTimeslotToReserve <= endTimeslot)
	{
		timeslotsToReserve.push(nextTimeslotToReserve);
		nextTimeslotToReserve += numberOfTicksPerTimeslot;
	}
	
	//todo check all cubes before reserve
	while (!timeslotsToReserve.empty())
	{
		if (reservationsTable[timeslotsToReserve.front()][std::pair<int,int>(cell.x,cell.y)])
		{
			argos::LOGERR << "ERROR: Timeslot already reserved. This should be checked before calling ReserveCell" << std::endl;
			return false;
		}
		reservationsTable[timeslotsToReserve.front()][std::pair<int,int>(cell.x,cell.y)] = true;
		timeslotsToReserve.pop();
	}

	return true;
}

void EnvironmentManager::PlacePod(Pod* pod, Coordinate cord)
{
	podParking[std::pair<int, int>(cord.x, cord.y)] = pod;
}

std::pair<int, int> EnvironmentManager::FindPodLocation(Pod* pod)
{
	std::map<std::pair<int,int>, Pod*>::iterator it;
	for ( it = podParking.begin(); it != podParking.end(); it++ )
	{
		if(it->second == pod)
			return it->first;
	}

	return std::pair<int, int>(-1, -1);
}

int EnvironmentManager::GetPodID(std::pair<int, int> coordinate)
{

	std::map<std::pair<int,int>, Pod*>::iterator it;
	for(it = podParking.begin(); it != podParking.end(); it++)
	{
		if(it->first.first == coordinate.first &&
			it->first.second == coordinate.second)
		{
			return it->second->getId();
		}
	}

	return -1;
}

bool EnvironmentManager::PickUpPod(int podID, std::pair<int,int> coordinate)
{
	//Is the requested pod on the giving location?
	int actualID = GetPodID(coordinate);
	if(actualID != podID)
		return false;

	podParking.erase(coordinate);
	
	return true;
}

bool EnvironmentManager::PutDownPod(int podID, std::pair<int,int> coordinate)
{
	//Is the giving coordinate occupied?
	int currentID = GetPodID(coordinate);
	if(currentID != -1)
		return false;

	Pod* podPtr = wh->pm.GetPodPtr(podID);
	PlacePod(podPtr, Coordinate(coordinate.first, coordinate.second));

	return true;
}

int EnvironmentManager::GetTimeslot(int tick)
{
	int result = -1;

	for (int i = currentTimeslots[0]; i < timeslotsIntoTheFuture; i++)
	{
		if (tick < currentTimeslots[i+1]){
			result = currentTimeslots[i];
			break;
		}
	}

	return result;
}


#endif
