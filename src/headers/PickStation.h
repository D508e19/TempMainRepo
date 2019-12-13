#ifndef PICKSTATION_H
#define PICKSTATION_H

#include <stdlib.h>
#include <queue>
#include <deque>

class PickStation
{
private:
    Warehouse* wh;  
    
public:
    PickStation();
    ~PickStation();

    int id;
    std::pair<int,int> pickCoordinate;
    std::deque<Order*> activeOrders;

    void SetupPickStation(int _id, std::pair<int,int> _pickCoordinate, Warehouse* _wh);
    void Tick();
};

#endif