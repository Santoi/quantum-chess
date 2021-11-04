cmake_minimum_required(VERSION 3.12)

set(This chessman)

project(${This} C CXX)

set(Headers chessman.h tower.h bishop.h queen.h king.h chessman_container.h knight.h pawn.h)
set(Sources chessman.cpp tower.cpp bishop.cpp queen.cpp king.cpp chessman_container.cpp knight.cpp pawn.cpp)

add_library(${This}-lib STATIC ${Sources} ${Headers})