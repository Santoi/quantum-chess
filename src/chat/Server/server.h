#ifndef QUANTUM_CHESS_PROJ_SERVER_H
#define QUANTUM_CHESS_PROJ_SERVER_H

#include <list>
#include "common_socket.h"
#include "client_handler.h"

#define SINGLE_THREADED_MATCH_AND_CLIENTS 1
#define SINGLE_THREADED_MATCH_AND_THREADED_CLIENTS 2
#define THREADED_MATCH_AND_THREADED_CLIENTS 3
#define MAX_CLIENTS 3

class Server {
private:
    Socket acceptor_socket;

public:
    Server() = delete;

    //Creates a new server, using the host and service parameters to create the acceptor_socket.
    Server(const char* host, const char* service);

    //Begins execution according to if the server is one_thread_only and type_of_single_thread.
    //If one_thread_only is false, then normal execution of the server is done.
    void execute(bool one_thread_only, int type_of_single_thread);

    ~Server() = default;

private:
    //Executes type of single threaded server according to the type_of_single_thread number.
    //If the number is equal to SINGLE_THREADED_MATCH_AND_CLIENTS, then server with single
    //threaded matches and clients is executed. If the number is equal to
    //SINGLE_THREADED_MATCH_AND_THREADED_CLIENTS then server with threaded clients but with
    //single-threaded matches is executed. If the number is equal to
    //THREADED_MATCH_AND_THREADED_CLIENTS, then all clients and matches have their threads.
    //Each one of these executions handle exactly up to MAX_CLIENTS.
    void executeSingleThreadedServer(int type_of_single_thread);

    void executeServerWithThreads();

    void executeAcceptorThread();

};

#endif //QUANTUM_CHESS_PROJ_SERVER_H
