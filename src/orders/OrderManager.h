#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <stdlib.h>
#include <time.h>

#include "Order.h"

class OrderManager
{
private:
	int m_orderCount;
	int m_numberOfPods;
public:
	OrderManager();
	OrderManager(int numOfPods);
	~OrderManager();

	Order getNewOrder();
};

OrderManager::OrderManager(){}

OrderManager::OrderManager(int numOfPods): m_orderCount(0), m_numberOfPods(numOfPods)
{
	srand (time(NULL));	// seed
}

OrderManager::~OrderManager(){}

Order OrderManager::getNewOrder()
   {
    int currentTime = -1; // placeholder
    int sid = rand() % m_numberOfPods;
    Order newOrder(m_orderCount++, currentTime, sid);
    return newOrder;
}


#endif
