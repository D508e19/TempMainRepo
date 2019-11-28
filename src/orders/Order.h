#ifndef ORDER_H
#define ORDER_H

class Order
{
private:
	int orderID;
	int podID;
	int timestamp_born;
	int timestamp_assigned;
	int timestamp_completed;
	bool underWay;
	
public:
	Order();
	Order(int orderID, int timestampBorn);
	~Order();

    int getPodID(){ return Order::podID; }
    int getOrderID(){ return Order::orderID; }
};

Order::Order(){};

Order::Order(int orderID, int timestampBorn):
	orderID(orderID), 
    timestamp_born(timestampBorn), 
	underWay(false)
    {};

Order::~Order(){}


#endif
