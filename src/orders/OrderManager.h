#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <stdlib.h>
#include <time.h>

#include "Order.h"

// forward declaration
//class Warehouse;

class OrderManager
{
private:
	int m_orderCount;
	int m_numberOfPods;

	Warehouse *wh;

public:
	OrderManager();
	~OrderManager();

	void SetupOrderManager(Warehouse *_wh);
	void Tick();

	Order getNewOrder();
};

OrderManager::OrderManager(){}
OrderManager::~OrderManager(){}

void OrderManager::Tick()
{

};

void OrderManager::SetupOrderManager(Warehouse* _wh)
{
	wh = _wh;
	m_orderCount = 0;

}

Order OrderManager::getNewOrder()
   {
	// placeholder
    int currentTime = -1; 
    int sid = rand() % m_numberOfPods;
    Order newOrder(m_orderCount++, currentTime, sid);
    return newOrder;
}

#endif
