cmake_minimum_required(VERSION 3.12)

set(This quantum-chess-proj)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(googletest)
add_subdirectory(src)
add_subdirectory(test)