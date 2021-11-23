#ifndef QUANTUM_CHESS_PROJ_SERVER_H
#define QUANTUM_CHESS_PROJ_SERVER_H

#include <list>
#include "../../common/src/socket.h"
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
  Server(const char *host, const char *service);

  //Begins execution according to if the server is one_thread_only and type_of_single_thread.
  //If one_thread_only is false, then normal execution of the server is done.
  void execute();

  ~Server() = default;
};

#endif //QUANTUM_CHESS_PROJ_SERVER_H
