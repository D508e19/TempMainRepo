add_library(alibot SHARED alibot.h alibot.cpp)
target_link_libraries(alibot
  argos3core_simulator
  argos3plugin_simulator_footbot
  argos3plugin_simulator_genericrobot)