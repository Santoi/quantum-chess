cmake_minimum_required(VERSION 3.12)

set(This ascii-chess)

project(${This} C CXX)

set(Headers ascii_chess.h)
set(Sources ascii_chess.cpp main.cpp)

add_executable(${This} ${Sources} ${Headers})

target_link_libraries(${This} quantum-chess-lib)