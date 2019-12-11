#ifndef PICKSTATION_CPP
#define PICKSTATION_CPP

#include <stdlib.h>
#include <time.h>
#include <queue>

PickStation::PickStation(int _id, std::pair<int,int> _pickCoordinate)
{
    id = _id;
    pickCoordinate = _pickCoordinate;
}

PickStation::~PickStation(){}

void PickStation::Tick()
{
    argos::LOG << "Pick station Tick: " << id << std::endl;
}

void PickStation::AddTask(Order* order)
{
    tasks.push_front(order);
}


#endif