cmake_minimum_required(VERSION 3.12)

set(This chessman)

project(${This} C CXX)

set(Headers chessman.h tower.h bishop.h)
set(Sources chessman.cpp tower.cpp bishop.cpp)

add_library(${This}-lib STATIC ${Sources} ${Headers})