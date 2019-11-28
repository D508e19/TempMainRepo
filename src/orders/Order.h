#ifndef ORDER_H
#define ORDER_H

class Order
{
private:
	const int m_orderID;
	const int m_PodID;
	const int m_timestamp_born;
	int m_timestamp_completed;
	bool underWay;

public:
	Order(int orderID, int timestampBorn, int PodID);
	~Order();

	int getPodID() { return Order::m_PodID; }
	int getOrderID() { return Order::m_orderID; }
};
#endif
