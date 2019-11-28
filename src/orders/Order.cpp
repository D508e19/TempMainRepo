#include "Order.h"

Order::Order(int orderID, int timestampBorn, int PodID) : m_orderID(orderID),
                                                          m_timestamp_born(timestampBorn),
                                                          m_PodID(PodID),
                                                          underWay(false){};

Order::~Order() {}
