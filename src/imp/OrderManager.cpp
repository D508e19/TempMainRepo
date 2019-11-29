#ifndef ORDERMANAGER_CPP
#define ORDERMANAGER_CPP

#include <stdlib.h>
#include <time.h>
#include <queue>

OrderManager::OrderManager(){}
OrderManager::~OrderManager(){}

void OrderManager::Tick()
{
	int tempSize = ordersToBeProcessed.size();
    for (int i = 0; i < tempSize; i++)
    {
		int nextId = ordersToBeProcessed.front();
        argos::LOG << "process order id: " << orders[nextId].getOrderID() << std::endl;

		// can først virke når vi afskiller h og cpp filer
		//wh->AddOrderToProcessQueue(&orders[i]);

		ordersToBeProcessed.pop();
    }
}

void OrderManager::SetupOrderManager(Warehouse* _wh)
{
	wh = _wh;
	orderCount = 0;
	argos::LOG << orderCount << std::endl;
	for (int i = 0; i < 10; i++)
	{
		CreateOrder();
	}
}

void OrderManager::CreateOrder()
{
    Order newOrder(orderCount, -1);
	ordersToBeProcessed.push(newOrder.getOrderID());
	orders.insert(std::pair<int, Order> (orderCount, newOrder));
	argos::LOG << "created order: " << newOrder.getOrderID() << std::endl;
	orderCount++;
}

#endif
