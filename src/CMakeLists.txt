cmake_minimum_required(VERSION 3.12)

set(This quantum-chess)

project(${This} C CXX)

set(Headers chessman/chessman.h quantum_position_tree.h position.h board.h)
set(Sources chessman/chessman.cpp quantum_position_tree.cpp position.cpp board.cpp)

add_subdirectory(chessman)

add_executable(${This} main.cpp ${Sources} ${Headers})

add_library(${This}-lib STATIC ${Sources} ${Headers})

target_link_libraries(${This} chessman-lib)
target_link_libraries(${This}-lib chessman-lib)