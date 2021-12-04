#include "clients_threads.h"
#include "server_protocol.h"
#include "instructions/instruction.h"
#include "../../common/src/socket_closed.h"
#include "iostream"
#include "instructions/exit_instruction.h"

ClientHandlersReceiver::ClientHandlersReceiver(Socket &socket,
                                               const ClientData &client_data_,
                                               BlockingQueue<Instruction> &
                                               updates_queue)
        : client_socket(socket), client_data(client_data_),
          updates_queue(updates_queue) {
}

ClientHandlersReceiver::ClientHandlersReceiver(
        ClientHandlersReceiver &&otherReceiver, Socket &socket)
        : Thread(std::move(otherReceiver)), client_socket(socket),
          client_data(otherReceiver.client_data),
          updates_queue(otherReceiver.updates_queue) {
}

void ClientHandlersReceiver::receiveInstructionAndPushToQueue() {
  std::shared_ptr<Instruction> ptr_instruction;
  ServerProtocol protocol;
  protocol.fillInstructions(this->client_socket, client_data, ptr_instruction);
  this->updates_queue.push(ptr_instruction);
}

void ClientHandlersReceiver::pushToQueueExitInstruction() {
  std::shared_ptr<Instruction> exit_instruction = std::make_shared<ExitInstruction>(
          client_data);
  this->updates_queue.push(exit_instruction);
}

void ClientHandlersReceiver::run() {
  try {
    while (true)
      this->receiveInstructionAndPushToQueue();
  }
  catch (const SocketClosed &error) {
    std::cerr << "Client id " << client_data.id << " " << error.what()
              << std::endl;
    this->pushToQueueExitInstruction();
  }
}

ClientHandlersSender::ClientHandlersSender(Socket &socket,
                                           BlockingQueue<Instruction> &notifications_queue,
                                           const ClientData &client_data_)
        : client_socket(socket), client_data(client_data_),
          notifications_queue(notifications_queue) {
}


ClientHandlersSender::ClientHandlersSender(ClientHandlersSender &&otherSender,
                                           Socket &socket)
        : client_socket(socket), client_data(otherSender.client_data),
          notifications_queue(otherSender.notifications_queue) {
}

void ClientHandlersSender::popFromQueueAndSendInstruction() {
  auto instruct_ptr = notifications_queue.pop();
  ServerProtocol protocol;
  protocol.sendPacketWithUpdates(this->client_socket, instruct_ptr,
                                 client_data);
}

void ClientHandlersSender::run() {
  try {
    while (true)
      this->popFromQueueAndSendInstruction();
  }
  catch (const BlockingQueueClosed &e) {}
}