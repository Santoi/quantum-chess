cmake_minimum_required(VERSION 3.12)

set(This server)

project(${This} C CXX)

set(Headers blocking_queue.h client_handler.h clients_threads.h common_packet.h common_socket.h common_socket_closed.h instructions.h match.h matches_repository.h
        nick_names_repository.h protocol.h server.h server_protocol.h thread.h thread_safe_queue.h unique_ptr.h)
set(Sources blocking_queue.cpp client_handler.cpp clients_threads.cpp common_packet.cpp common_socket.cpp common_packet.cpp instructions.cpp match.cpp matches_repository.cpp
        nick_names_repository.cpp protocol.cpp server.cpp server_protocol.cpp thread.cpp thread_safe_queue.cpp)

add_executable(${This} ${Sources} ${Headers} main.cpp)

target_link_libraries(${This} pthread)