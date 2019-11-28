#include "OrderManager.h"

OrderManager::OrderManager() {}
OrderManager::~OrderManager() {}

void OrderManager::Tick(){

};

void OrderManager::SetupOrderManager(Warehouse *_wh)
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
