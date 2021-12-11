cmake_minimum_required(VERSION 3.12)

set(This chessman)

project(${This} C CXX)

file(GLOB Sources "*.cpp")

file(GLOB Headers "*.h")

add_library(${This}-lib STATIC ${Sources} ${Headers})