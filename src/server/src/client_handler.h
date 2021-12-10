#ifndef QUANTUM_CHESS_PROJ_CLIENT_HANDLER_H
#define QUANTUM_CHESS_PROJ_CLIENT_HANDLER_H

#include <thread>
#include <memory>
#include "clients_map.h"
#include "../../common/src/socket.h"
#include "../../common/src/blocking_queue.h"
#include "clients_threads.h"
#include "server_protocol.h"

class Instruction;

// Handles clients sender and receiver threads. Store client data.
class ClientHandler {
private:
  Socket client_socket;
  BlockingQueue<Instruction> &notifications_queue;
  const ClientData client_data;
  ClientHandlersReceiver client_receiver;
  ClientHandlersSender client_sender;

public:
  ClientHandler() = delete;

  ClientHandler(Socket &&socket,
                BlockingQueue<Instruction> &notifications_queue,
                BlockingQueue<Instruction> &updates_queue,
                ClientData client_data_);

  ClientHandler(ClientHandler &&other_client) noexcept;

  // Starts sender and receiver threads.
  void start();

  // Returns a reference to client data.
  const ClientData &getData() const;

  // Joins both the handler's receiver and sender threads.
  void join();

  // Stops both thread by closing socket and closing notifications queue.
  void stop();

  ~ClientHandler() = default;
};


#endif //QUANTUM_CHESS_PROJ_CLIENT_HANDLER_H
