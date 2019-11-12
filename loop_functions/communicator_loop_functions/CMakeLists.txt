link_directories(${CMAKE_BINARY_DIR}/controllers/alibot)

set(communicator_loop_functions_SOURCES
  communicator_loop_functions.h
  communicator_loop_functions.cpp ../../environment/node.cpp ../../environment/node.h)

add_library(communicator_loop_functions MODULE 
  ${communicator_loop_functions_SOURCES})
target_link_libraries(communicator_loop_functions
  alibot
  argos3core_simulator
  argos3plugin_simulator_entities
  argos3plugin_simulator_footbot)