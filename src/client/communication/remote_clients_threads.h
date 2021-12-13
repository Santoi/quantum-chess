#ifndef QUANTUM_CHESS_PROJ_REMOTE_CLIENTS_THREADS_H
#define QUANTUM_CHESS_PROJ_REMOTE_CLIENTS_THREADS_H

#include "../../common/thread.h"
#include <string>
#include "../../common/socket.h"
#include "remote_client_instructions.h"
#include "../../common/blocking_queue.h"

class RemoteClientSender : public Thread {
private:
  Socket &client_socket;
  BlockingQueue<RemoteClientInstruction> &send_queue;
  bool sender_is_active;

public:
  RemoteClientSender() = delete;

  //Creates a RemoteClientSender, saving a reference to client_socket.
  RemoteClientSender(Socket &client_socket,
                     BlockingQueue<RemoteClientInstruction> &send_queue_);

  ~RemoteClientSender() override = default;

protected:
  // Pops instructions from queue until queue its closed
  void run() override;
};

class RemoteClientReceiver : public Thread {
private:
  Socket &client_socket;
  BlockingQueue<RemoteClientInstruction> &queue;
  bool socket_closed;

public:
  RemoteClientReceiver() = delete;

  // Creates a RemoteClientReceiver, saving a reference to client_socket
  RemoteClientReceiver(Socket &client_socket,
                       BlockingQueue<RemoteClientInstruction> &queue_);

  // Receive instruction and push it into the client instruction queue
  void receiveMessage();

  void notifySocketClosed();

  ~RemoteClientReceiver() override = default;

protected:
  // Receive messages until socket is closed
  void run() override;
};


#endif //QUANTUM_CHESS_PROJ_REMOTE_CLIENTS_THREADS_H
