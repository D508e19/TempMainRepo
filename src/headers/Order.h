#ifndef ORDER_H
#define ORDER_H

class Order
{
private:

public:
	Order(int orderID, int timestampBorn);
	~Order();

	int orderID = -1;
	int podID = -1;
	int timestamp_born = -1;
	int timestamp_assigned = -1;
	int timestamp_completed = -1;
	// bool underWay;

};


#endif
