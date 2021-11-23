#ifndef QUANTUM_CHESS_PROJ_CLIENT_HANDLER_H
#define QUANTUM_CHESS_PROJ_CLIENT_HANDLER_H


#include <thread>
#include <memory>
#include "../../common/src/socket.h"
#include "../../common/src/blocking_queue.h"
#include "clients_threads.h"
#include "match.h"
#include "server_protocol.h"


class Match;

class Instruction;

class ClientHandler {
private:
  Socket client_socket;
  BlockingQueue<Instruction> &notifications_queue;
  const ClientData client_data;
  ClientHandlersReceiver client_receiver;
  ClientHandlersSender client_sender;


public:
  ClientHandler() = delete;

  //A ClientHandler is created, moving and storing the given socket. A ClientHandlersReceiver and
  //ClientHandlersSender are also created and saved. The boolean client_is_active is set to true.
  ClientHandler(Socket &&socket,
                BlockingQueue<Instruction> &notifications_queue,
                BlockingQueue<Instruction> &updates_queue,
                ClientData client_data_);

  //Creates a new ClientHandler by moving the other_client's socket to the new handler, and creating
  //the new receivers and senders respectively. The new handler saves the other_client boolean
  //client_is_active.
  ClientHandler(ClientHandler &&other_client) noexcept;

  //Starts ClientHandler's threads by calling the private start method. If match has its own thread
  //(threaded_match is true), then the function ends. If threaded_match is false, while the boolean
  //client_is_active is true, the match is asked to check updates coming from the receiver's thread
  //and notify updates to the sender's thread.
  void startThreadedClient(Match &match);

  const ClientData &getData() const;

  //Joins (if joinable) both the handler's receiver and sender threads. Object's boolean
  //client_is_active is set to true.
  void join();

  void stop();

  ~ClientHandler() = default;
};


#endif //QUANTUM_CHESS_PROJ_CLIENT_HANDLER_H
