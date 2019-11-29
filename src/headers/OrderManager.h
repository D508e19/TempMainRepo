#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <stdlib.h>
#include <time.h>
#include <queue>


class OrderManager
{
private:
	int orderCount;


    std::map<int, Order> orders; //alle ordre
	std::queue<int> ordersToBeProcessed;

	Warehouse *wh;

public:
	OrderManager();
	~OrderManager();

	void SetupOrderManager(Warehouse *_wh);
	void Tick();

	void CreateOrder();
};


#endif
