cmake_minimum_required(VERSION 3.12)

set(This client)

project(${This} C CXX)

file(GLOB Sources "*.cpp")

file(GLOB Headers "*.h")

add_executable(${This} ${Sources} ${Headers})

target_link_libraries(${This} common)