cmake_minimum_required(VERSION 3.12)

set(This quantum-chess-test)

file(GLOB Tests "*.cpp")

add_executable(${This} ${Tests})
target_link_libraries(${This} PUBLIC
    gtest_main
    quantum-chess-lib
)

add_test(
        NAME ${This}
        COMMAND ${This}
)