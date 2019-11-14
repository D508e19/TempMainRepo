set(Orders_SOURCES
  Order.h
  OrderManager.h)

add_library(Orders MODULE
  ${orders_SOURCES})
target_link_libraries(Orders
  argos3core_simulator
  argos3plugin_simulator_entities
  argos3plugin_simulator_footbot)