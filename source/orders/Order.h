#ifndef ORDER_H
#define ORDER_H

class Order
{
private:
	int m_orderID;
	int m_timestamp_born;
	int m_timestamp_completed;
	int m_PodID;
public:
	Order(int orderID, int timestampBorn, int PodID);
	~Order();

    int getPodID(){ return Order::m_PodID; }
    int getOrderID(){ return Order::m_orderID; }
};

Order::Order(int orderID, int timestampBorn, int PodID):
	m_orderID(orderID), 
    m_timestamp_born(timestampBorn), 
    m_PodID(PodID) 
    {};

Order::~Order(){}


#endif
