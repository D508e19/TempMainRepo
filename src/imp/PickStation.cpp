#ifndef PICKSTATION_CPP
#define PICKSTATION_CPP

#include <stdlib.h>
#include <time.h>
#include <queue>
#include <deque>

PickStation::PickStation(){}
PickStation::~PickStation(){}

void PickStation::SetupPickStation(int _id, std::pair<int,int> _pickCoordinate, Warehouse* _wh)
{
    wh = _wh;
    id = _id;
    pickCoordinate = _pickCoordinate;
}

void PickStation::Tick()
{
    for(auto order : activeOrders)
    {
        //Is the pod of the order in the pick location? = Complete order
        if((order->podPtr->location.first == pickCoordinate.first) &&  (order->podPtr->location.second == pickCoordinate.second))
        {
            order->timestamp_completed = wh->em->tickCounter;
            auto it = std::find_if(activeOrders.begin(), activeOrders.end(), [order](const Order* i) {return order == i;});
            activeOrders.erase(it);
        }
    }
}

#endif