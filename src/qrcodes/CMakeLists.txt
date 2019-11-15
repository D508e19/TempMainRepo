set(QRCODES_SOURCES
  QRCode.h)

add_library(QRCodes MODULE
  ${QRCODES_SOURCES})
target_link_libraries(QRCodes
  argos3core_simulator
  argos3plugin_simulator_entities
  argos3plugin_simulator_footbot)