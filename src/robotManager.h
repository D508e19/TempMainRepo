#ifndef ROBOTMANAGER_H
#define ROBOTMANAGER_H

#include "orders/Order.h"
#include "qrcodes/QRcode.h"

class robotManager
{
private:

public:
    robotManager();
    ~robotManager();

    Order RequestOrder();
    bool CompleteOrder();
    QRCode GetCellQR();
    QRCode GetPodQR();

};

robotManager::robotManager(){}

robotManager::~robotManager(){}


#endif
