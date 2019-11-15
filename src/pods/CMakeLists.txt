set(Pods_SOURCES
  Pod.h
  PodsManager.h)

add_library(Pods MODULE
  ${pods_SOURCES})
target_link_libraries(Pods
  argos3core_simulator
  argos3plugin_simulator_entities
  argos3plugin_simulator_footbot)