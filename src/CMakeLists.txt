cmake_minimum_required(VERSION 3.12)

set(This quantum-chess-src)

project(${This} C CXX)

add_subdirectory(server/src)
add_subdirectory(client/src)
add_subdirectory(common/src)
add_subdirectory(ascii_chess)
