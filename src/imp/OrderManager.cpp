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

	// TODO delete 
	for (int i = 0; i < 100; i++)
	{
		CreateOrder();
	}
}

void OrderManager::Tick()
{
	while(orderToBeReleased.size() > 0 && orderToBeReleased.front().first <= wh->em->tickCounter)
	{
		//argos::LOG << "Releasing order that has tick: " << orderToBeReleased.front().first << std::endl;
		Order* nextOrder = orderToBeReleased.front().second;
		wh->pm.ordersToBeProcessed.push(nextOrder);
		orderToBeReleased.pop();
	}
}

void OrderManager::CreateOrder()
{
    Order* newOrder = new Order(orderCount, -1);
	newOrder->wareID = newOrder->orderID; //TODO Temporary
	orders.insert(std::pair<int, Order*> (orderCount, newOrder)); //All orders queue
	ordersOngoing.push(newOrder); //Non-completed orders
	orderToBeReleased.push(std::pair<int, Order*> (orderCount, newOrder)); //To be released
	orderCount++;
}

#endif
