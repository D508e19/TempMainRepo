#ifndef ROBOTMANAGER_H
#define ROBOTMANAGER_H

#include <list>

#include "orders/Order.h"
#include "qrcodes/QRcode.h"

class robotManager
{
private:

public:
    robotManager();
    //robotManager(std::map<int, Basicbot*>);
    ~robotManager();

    Order RequestOrder();
    bool CompleteOrder();
    QRCode GetCellQR();
    QRCode GetPodQR();

};

robotManager::robotManager(){}

robotManager::~robotManager(){}


#endif
