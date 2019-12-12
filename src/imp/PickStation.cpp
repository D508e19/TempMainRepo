#ifndef PICKSTATION_CPP
#define PICKSTATION_CPP

#include <stdlib.h>
#include <time.h>
#include <queue>
#include <deque>

PickStation::PickStation(int _id, std::pair<int,int> _pickCoordinate, Warehouse* _wh)
{
    wh = _wh;
    id = _id;
    pickCoordinate = _pickCoordinate;
}

PickStation::~PickStation(){}

void PickStation::Tick()
{
    for(auto t : tasks)
    {
        //Is the pod of the order in the pick location? = Complete order
        if((tasks.front()->podPtr->location.first == pickCoordinate.first) &&  (tasks.front()->podPtr->location.second == pickCoordinate.second))
        {
            tasks.front()->timestamp_completed = wh->em->tickCounter;
            tasks.pop_front();
        }
    }
}


#endif