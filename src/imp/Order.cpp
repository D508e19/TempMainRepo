#ifndef ORDER_CPP
#define ORDER_CPP

Order::Order(){};

Order::Order(int orderID, int timestampBorn):
	orderID(orderID), 
    timestamp_born(timestampBorn), 
	underWay(false)
    {};

Order::~Order(){}


#endif
