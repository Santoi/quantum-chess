cmake_minimum_required(VERSION 3.12)

set(This quantum-chess)

project(${This} C CXX)

set(Headers chessman.h)
set(Sources chessman.cpp)

add_executable(${This} main.cpp ${Sources} ${Headers})

add_library(${This}-lib STATIC ${Sources} ${Headers})