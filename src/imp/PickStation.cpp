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
            argos::LOG << "Order: " << order->orderID << " is complete." << std::endl;
            order->timestamp_completed = wh->em->tickCounter;

            argos::LOG << "Tick born: " << order->timestamp_born << std::endl;
            argos::LOG << "Tick assigned: " << order->timestamp_assigned << std::endl;
            argos::LOG << "Tick completed: " << order->timestamp_completed << std::endl;

            auto it = std::find_if(activeOrders.begin(), activeOrders.end(), [order](const Order* i) {return order == i;});
            activeOrders.erase(it);
        }
    }
}

#endif