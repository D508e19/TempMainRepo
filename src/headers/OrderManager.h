#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <stdlib.h>
#include <time.h>
#include <queue>


class OrderManager
{
private:
	int orderCount;
    std::map<int, Order*> orders; //alle ordre
	Warehouse *wh;

public:
	OrderManager();
	~OrderManager();

	std::queue<Order*> ordersToBeProcessed;
	std::queue<Order*> ordersOngoing;

	void SetupOrderManager(Warehouse *_wh);
	void Tick();

	void CreateOrder();
};


#endif
