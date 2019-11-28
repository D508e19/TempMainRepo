#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <stdlib.h>
#include <time.h>

#include "Order.h"
#include "src/warehouse/Warehouse.h"

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

#endif
