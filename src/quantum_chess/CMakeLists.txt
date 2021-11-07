cmake_minimum_required(VERSION 3.12)

set(This quantum-chess-lib)

project(${This} C CXX)

set(Headers chessman/chessman.h position.h board.h chess_exception.h pseudo_random_coin.h quantum_position.h)
set(Sources chessman/chessman.cpp position.cpp board.cpp pseudo_random_coin.cpp quantum_position.cpp)

add_subdirectory(chessman)

add_library(${This} STATIC ${Sources} ${Headers})

target_link_libraries(${This} chessman-lib)