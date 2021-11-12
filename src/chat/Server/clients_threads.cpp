#include "clients_threads.h"
#include "server_protocol.h"
#include "instructions.h"


ClientHandlersReceiver::ClientHandlersReceiver(Socket& socket, const int& client_id, ThreadSafeQueue&
                                                updates_queue)
                        :client_socket(socket), client_id(client_id), updates_queue(updates_queue) {
}

ClientHandlersReceiver::ClientHandlersReceiver(ClientHandlersReceiver&& otherReceiver, Socket& socket)
                        :Thread(std::move(otherReceiver)), client_socket(socket), client_id(otherReceiver.client_id),
                         updates_queue(otherReceiver.updates_queue) {
}


void ClientHandlersReceiver::run() {
    std::shared_ptr<Instruction> ptr_instruction;
    ServerProtocol protocol;
    protocol.fillInstructionsWithPacket(this->client_socket, this->client_id, ptr_instruction);
    this->updates_queue.push(ptr_instruction);
}

