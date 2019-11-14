#ifndef ROBOTMANAGER_H
#define ROBOTMANAGER_H

#include <"Order.h>
#include <QRcode.h>

class robotManager
{
private:
    int m_controllerId;

public:
    robotManager(/* args */);
    ~robotManager();

    Order RequestOrder();
    bool CompleteOrder();
    QRCode GetCellQR();
    QRCode GetPodQR();

};

robotManager::robotManager(/* args */)
{
}

robotManager::~robotManager()
{
}


#endif