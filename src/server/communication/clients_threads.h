#ifndef QUANTUM_CHESS_PROJ_CLIENTS_THREADS_H
#define QUANTUM_CHESS_PROJ_CLIENTS_THREADS_H

#include "../../common/thread.h"
#include "../../common/socket.h"
#include "../../common/blocking_queue.h"
#include "../../common/client_data.h"

class Instruction;

// Thread that receive packets from client.
class ClientHandlersReceiver : public Thread {
private:
  Socket &client_socket;
  ClientData client_data;
  BlockingQueue<Instruction> &updates_queue;

public:
  ClientHandlersReceiver() = delete;

  ClientHandlersReceiver(Socket &socket, const ClientData &client_data_,
                         BlockingQueue<Instruction> &
                         updates_queue);

  ClientHandlersReceiver(ClientHandlersReceiver &&other_receiver,
                         Socket &socket);

  // Receives from socket, and pushes new instruction to the updates queue.
  void receiveInstructionAndPushToQueue();

  // Pushes an exit instruction to update queue to notify that the client left.
  void pushToQueueExitInstruction();

  ~ClientHandlersReceiver() override = default;

protected:
  // Receive from socket and push to updates queue.
  void run() override;
};

// Thread that send packets to client.
class ClientHandlersSender : public Thread {
private:
  Socket &client_socket;
  ClientData client_data;
  BlockingQueue<Instruction> &notifications_queue;

public:
  ClientHandlersSender() = delete;

  ClientHandlersSender(Socket &socket,
                       BlockingQueue<Instruction> &notifications_queue,
                       const ClientData &client_data_);

  ClientHandlersSender(ClientHandlersSender &&other_sender, Socket &socket);

  // Pops instructions from notifications queue and then send it from socket.
  void popFromQueueAndSendInstruction();

  ~ClientHandlersSender() override = default;

protected:
  // Pop from notifications queue and send to socket.
  void run() override;
};


#endif //QUANTUM_CHESS_PROJ_CLIENTS_THREADS_H
