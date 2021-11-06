cmake_minimum_required(VERSION 3.12)

set(This quantum-chess-lib)

project(${This} C CXX)

set(Headers chessman/chessman.h quantum_position_tree.h position.h board.h chess_exception.h)
set(Sources chessman/chessman.cpp quantum_position_tree.cpp position.cpp board.cpp)

add_subdirectory(chessman)

add_library(${This} STATIC ${Sources} ${Headers})

target_link_libraries(${This} chessman-lib)