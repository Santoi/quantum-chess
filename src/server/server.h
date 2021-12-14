#ifndef QUANTUM_CHESS_PROJ_SERVER_H
#define QUANTUM_CHESS_PROJ_SERVER_H

#include <list>
#include <string>
#include "../common/socket.h"
#include "communication/client_handler.h"

// Represents the server.
class Server {
private:
  Socket acceptor_socket;

public:
  Server() = delete;

  Server(const char *host, const char *service);

  // Executes server until 'q' is read from stdin
  void execute(const std::string &filename);

  ~Server() = default;
};

#endif //QUANTUM_CHESS_PROJ_SERVER_H
