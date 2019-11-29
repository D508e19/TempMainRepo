cmake_minimum_required(VERSION 3.10.2)

set(This Unit_Tests)

file(GLOB CPP_FILES unit_tests/*.cpp)
#test files here
set(Sources
    ${CPP_FILES}
)

add_executable(${This} ${Sources})


target_link_libraries(${This} PUBLIC
    gtest_main
    #libraries to test here


)

add_test(
    NAME ${This}
    COMMAND ${This}
)