cmake_minimum_required(VERSION 3.12)

set(This client)

project(${This} C CXX)

set(Headers client.h client_protocol.h common_packet.h common_socket.h common_socket_closed.h protocol.h remote_client_instructions.h
         remote_clients_threads.h thread.h)
set(Sources client.cpp client_protocol.cpp common_packet.cpp common_socket.cpp protocol.cpp remote_client_instructions.cpp remote_clients_threads.cpp
        thread.cpp)

add_executable(${This} ${Sources} ${Headers} main.cpp)

target_link_libraries(${This} quantum-chess-lib)