#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <stdlib.h>
#include <time.h>
#include <queue>


class OrderManager
{
private:
	int orderCount;
    
	std::queue<std::pair<int, Order*>> orderToBeReleased; //Orders generated, but not passed on.
	Warehouse *wh;

public:
	OrderManager();
	~OrderManager();

	std::map<int, Order*> orders; //all orders

	void SetupOrderManager(Warehouse *_wh);
	void Tick();

	void CreateOrder();
};


#endif
