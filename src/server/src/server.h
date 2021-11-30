#ifndef QUANTUM_CHESS_PROJ_SERVER_H
#define QUANTUM_CHESS_PROJ_SERVER_H

#include <list>
#include "../../common/src/socket.h"
#include "client_handler.h"

class Server {
private:
  Socket acceptor_socket;

public:
  Server() = delete;

  //Creates a new server, using the host and service parameters to create the acceptor_socket.
  Server(const char *host, const char *service);

  //Begins execution according to if the server is one_thread_only and type_of_single_thread.
  //If one_thread_only is false, then normal execution of the server is done.
  void execute(const std::string &filename);

  ~Server() = default;
};

#endif //QUANTUM_CHESS_PROJ_SERVER_H
