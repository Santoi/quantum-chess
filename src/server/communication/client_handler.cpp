#include "client_handler.h"

#include <utility>
#include "../../common/packet.h"
#include "instructions/instruction.h"
#include "../../common/socket_closed.h"


ClientHandler::ClientHandler(Socket &&socket,
                             BlockingQueue<Instruction> &notifications_queue,
                             BlockingQueue<Instruction> &
                             updates_queue, ClientData client_data_)
        : client_socket(std::move(socket)),
          notifications_queue(notifications_queue),
          client_data(std::move(client_data_)),
          client_receiver(client_socket, client_data, updates_queue),
          client_sender(client_socket, notifications_queue, client_data) {
}

ClientHandler::ClientHandler(ClientHandler &&other_client) noexcept:
        client_socket(std::move(other_client.client_socket)),
        notifications_queue(other_client.notifications_queue),
        client_data(other_client.client_data),
        client_receiver(std::move(other_client.client_receiver),
                        client_socket),
        client_sender(std::move(other_client.client_sender), client_socket) {
}

void ClientHandler::start() {
  client_receiver.start();
  client_sender.start();
}

void ClientHandler::stop() {
  client_socket.shutdownAndClose();
  notifications_queue.close();
}

void ClientHandler::join() {
  this->client_receiver.join();
  this->client_sender.join();
}

const ClientData &ClientHandler::getData() const {
  return client_data;
}
