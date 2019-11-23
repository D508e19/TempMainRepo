add_library(basicbot SHARED basicbot.h basicbot.cpp ${communicator_loop_functions_SOURCES} )

target_link_libraries(basicbot
  argos3core_simulator
  argos3plugin_simulator_footbot
  argos3plugin_simulator_genericrobot)