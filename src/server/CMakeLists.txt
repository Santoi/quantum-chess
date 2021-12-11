cmake_minimum_required(VERSION 3.12)

set(This server)

project(${This} C CXX)

file(GLOB Sources "*.cpp")

file(GLOB Headers "*.h")

add_executable(${This} ${Sources} ${Headers} main.cpp)

add_subdirectory(quantum_chess)
add_subdirectory(communication)

target_link_libraries(${This} common communication-server-lib quantum-chess-lib)
