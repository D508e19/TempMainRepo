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

	// Temporary generation of orders
	for (int i = 0; i < numberOfOrdersToGenerate; i++)
	{
		CreateOrder();
	}
}

void OrderManager::Tick()
{
	//Pass on orders which release tick is same or lower than current tick
	while(orderToBeReleased.size() > 0 && orderToBeReleased.front().first <= wh->em->tickCounter)
	{
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
	//ordersOngoing.push(newOrder); //Non-completed orders
	orderToBeReleased.push(std::pair<int, Order*> (orderCount * tickSpaceBetweenOrders, newOrder)); //To be released
	orderCount++;
}

#endif
