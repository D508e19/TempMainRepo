#ifndef PICKSTATION_CPP
#define PICKSTATION_CPP

#include <stdlib.h>
#include <time.h>
#include <queue>

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
        if(t->podLocation.first == pickCoordinate.first &&  t->podLocation.second == pickCoordinate.second)
        {
            argos::LOG << "PickStation: Order completed. Order id: " << t->orderID << std::endl;
            t->timestamp_completed = wh->em->tickCounter;
            tasks.remove(t);
            
        }
    }
}

void PickStation::AddTask(Order* order)
{
    tasks.push_front(order);
}


#endif