cmake_minimum_required(VERSION 3.10.2)

set(This Unit_Tests)

###############################################################################
## file globbing ##############################################################
###############################################################################

# These instructions search the directory tree when cmake is
# invoked and put all files that match the pattern in the variables
# `sources` and `data`.
#file(GLOB_RECURSE sources      src/main/*.cpp src/main/*.h)
#file(GLOB_RECURSE sources_test tests/unit_tests/*.cpp)
#file(GLOB_RECURSE data resources/*)
# You can use set(sources src/main.cpp) etc if you don't want to
# use globbing to find files automatically.

#test files here
include_directories(${CMAKE_SOURCE_DIR} ${ARGOS_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})
file(GLOB_RECURSE sources_test unit_tests/*.cpp)

add_executable(${This} ${sources_test})


target_link_libraries(${This} PUBLIC
    gtest_main

    #libraries to test here


)

add_test(
    NAME ${This}
    COMMAND ${This}
)