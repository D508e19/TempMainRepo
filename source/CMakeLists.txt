include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(orders)
add_subdirectory(pods)

set(RobotManager_SOURCES
  RobotManager.h)

add_library(RobotManager MODULE
  ${source_SOURCES})
target_link_libraries(Pods
  argos3core_simulator
  argos3plugin_simulator_entities
  argos3plugin_simulator_footbot)