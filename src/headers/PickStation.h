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
    PickStation(int _id, std::pair<int,int> _pickCoordinate, Warehouse* _wh);
    ~PickStation();

    int id;
    std::pair<int,int> pickCoordinate;
    std::deque<Order*> tasks;

    void Tick();
    void AddTask(Order* order);
};

#endif