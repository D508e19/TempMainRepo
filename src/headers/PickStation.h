#ifndef PICKSTATION_H
#define PICKSTATION_H

#include <stdlib.h>
#include <queue>

class PickStation
{
private:
    int id;
    
    std::list<Order*> tasks;
public:
    PickStation(int _id, std::pair<int,int> _pickCoordinate);
    ~PickStation();

    std::pair<int,int> pickCoordinate;

    void Tick();
};

#endif