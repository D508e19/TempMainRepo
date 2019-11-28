set(ORDERS_SOURCES
  Order.h
  OrderManager.h
  Order.cpp
  OrderManager.cpp)

add_library(ORDERS SHARED
  ${ORDERS_SOURCES})
