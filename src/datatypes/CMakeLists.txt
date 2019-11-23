set(CUSTOMDATATYPES_SOURCES
        Coordinate.h
        ds_instruction.h
        Path.h
        )

add_library(CUSTOMDATATYPES SHARED
  ${CUSTOMDATATYPES_SOURCES})
