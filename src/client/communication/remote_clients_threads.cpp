#include "remote_clients_threads.h"
#include <string>
#include "client_protocol.h"
#include <iostream>
#include "remote_client_instructions.h"
#include "../../common/blocking_queue.h"
#include "../../common/socket_closed.h"

RemoteClientSender::
RemoteClientSender(Socket &client_socket,
                   BlockingQueue<RemoteClientInstruction> &send_queue_)
    : client_socket(client_socket), send_queue(send_queue_) {
}

void RemoteClientSender::run() {
  ClientProtocol protocol;
  try {
    while (true) {
      auto instruction = send_queue.pop();
      protocol.sendInstruction(client_socket, instruction);
    }
  }
  catch(const BlockingQueueClosed &e) {}
}


RemoteClientReceiver::
RemoteClientReceiver(Socket &client_socket,
                     BlockingQueue<RemoteClientInstruction> &queue_)
    : client_socket(client_socket), queue(queue_), socket_closed(false) {}

void RemoteClientReceiver::receiveMessage() {
  std::shared_ptr<RemoteClientInstruction> ptr_instruction;
  ClientProtocol protocol;
  protocol.receiveInstruction(this->client_socket, ptr_instruction);
  queue.push(ptr_instruction);
}

void RemoteClientReceiver::run() {
  try {
    while (true)
      this->receiveMessage();
  }
  catch(const SocketClosed &e) {
    if (!socket_closed)
      std::cerr << "Error: connection with server lost" << std::endl;
  }
}

void RemoteClientReceiver::notifySocketClosed() {
  socket_closed = true;
}
