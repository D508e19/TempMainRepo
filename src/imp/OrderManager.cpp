#ifndef ORDERMANAGER_CPP
#define ORDERMANAGER_CPP

#include <stdlib.h>
#include <time.h>
#include <queue>

OrderManager::OrderManager(){}
OrderManager::~OrderManager(){}

void OrderManager::SetupOrderManager(Warehouse* _wh)
{
	wh = _wh;
	orderCount = 0;

	// /* TODO delete 
	for (int i = 0; i < 100; i++)
	{
		CreateOrder();
	}
	// */
}

void OrderManager::Tick()
{
	// new orders to be created?
	// old orders to be closed? need a ordersToBeProcessed queue?
}

void OrderManager::CreateOrder()
{
	//argos::LOG << "create order with id: " << orderCount << std::endl;
    Order* newOrder = new Order(orderCount, -1);
	newOrder->wareID = newOrder->orderID; //TODO Temporary
	orders.insert(std::pair<int, Order*> (orderCount, newOrder));
	wh->pm.ordersToBeProcessed.push(newOrder);
	ordersOngoing.push(newOrder);
	
	orderCount++;
}

#endif
