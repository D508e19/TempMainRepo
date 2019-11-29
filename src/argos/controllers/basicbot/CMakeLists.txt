add_library(basicbot SHARED basicbot.h basicbot.cpp)
target_link_libraries(basicbot
  argos3core_simulator
  argos3plugin_simulator_footbot
  argos3plugin_simulator_genericrobot)