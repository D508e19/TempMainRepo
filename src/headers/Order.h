#ifndef ORDER_H
#define ORDER_H

class Order
{
private:

public:
	Order(int orderID, int timestampBorn);
	~Order();

	int orderID = -1;
	int wareID = -1;
	int podID = -1;
	std::pair<int, int> podLocation = std::pair<int, int>(-1, -1);
	std::pair<int, int> pickStationLocation = std::pair<int, int>(-1, -1);
	int timestamp_born = -1;
	int timestamp_assigned = -1;
	int timestamp_completed = -1;

};


#endif
