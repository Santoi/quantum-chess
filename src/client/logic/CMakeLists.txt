cmake_minimum_required(VERSION 3.12)

set(This logic-lib)

project(${This} C CXX)

file(GLOB Sources "*.cpp")
file(GLOB Headers "*.h")

add_library(${This} STATIC ${Sources} ${Headers})

target_link_libraries(${This} sdl-lib)
