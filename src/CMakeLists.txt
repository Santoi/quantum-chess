cmake_minimum_required(VERSION 3.12)

set(This quantum-chess-src)

project(${This} C CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O3 -ggdb -DDEBUG -fno-inline -D _POSIX_C_SOURCE=200809L")

add_subdirectory(server/src)
add_subdirectory(common/src)
add_subdirectory(client)
add_subdirectory(ascii_chess)

