#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <stdlib.h>
#include <time.h>
#include <queue>


class OrderManager
{
private:
	int orderCount;
	Warehouse *wh;

public:
	OrderManager();
	~OrderManager();

    std::map<int, Order*> orders; //alle ordre
	std::queue<Order*> ordersToBeProcessed;
	std::queue<Order*> ordersOngoing;

	void SetupOrderManager(Warehouse *_wh);
	void Tick();

	void CreateOrder();
};


#endif
