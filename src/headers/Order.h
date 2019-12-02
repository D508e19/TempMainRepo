#ifndef ORDER_H
#define ORDER_H

class Order
{
private:

public:
	Order(int orderID, int timestampBorn);
	~Order();

	int orderID = -1;
	int podID;
	int timestamp_born;
	int timestamp_assigned;
	int timestamp_completed;
	bool underWay;

};


#endif
