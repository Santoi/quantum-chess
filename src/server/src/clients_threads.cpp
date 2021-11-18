#include "clients_threads.h"
#include "server_protocol.h"
#include "instructions/instruction.h"
#include "../../common/src/socket_closed.h"
#include "iostream"
#include "instructions/exit_instruction.h"

ClientHandlersReceiver::ClientHandlersReceiver(Socket& socket, const int& client_id, BlockingQueue<Instruction>&
                                                updates_queue)
                        :client_socket(socket), client_id(client_id), updates_queue(updates_queue) {
}

ClientHandlersReceiver::ClientHandlersReceiver(ClientHandlersReceiver&& otherReceiver, Socket& socket)
                        :Thread(std::move(otherReceiver)), client_socket(socket), client_id(otherReceiver.client_id),
                         updates_queue(otherReceiver.updates_queue) {
}

void ClientHandlersReceiver::receiveInstructionAndPushToQueue() {
    std::shared_ptr <Instruction> ptr_instruction;
    ServerProtocol protocol;
    protocol.fillInstructions(this->client_socket, this->client_id, ptr_instruction);
    this->updates_queue.push(ptr_instruction);
}

void ClientHandlersReceiver::pushToQueueExitInstruction() {
    std::shared_ptr <Instruction> exit_instruction = std::make_shared<ExitInstruction>(this->client_id);
    this->updates_queue.push(exit_instruction);
}

void ClientHandlersReceiver::run() {
    try{
        while (true)
            this->receiveInstructionAndPushToQueue();
    }
    catch (const SocketClosed& error) {
        std::cerr << "Client id" << client_id << " " << error.what() << std::endl;
        this->pushToQueueExitInstruction();
    }
}

ClientHandlersSender::ClientHandlersSender(Socket& socket, BlockingQueue<Instruction>& notifications_queue,
                                           const int& client_id, const NickNamesRepository& nick_names)
                      :client_socket(socket), client_id(client_id),
                       notifications_queue(notifications_queue), nick_names(nick_names) {
}


ClientHandlersSender::ClientHandlersSender(ClientHandlersSender&& otherSender, Socket& socket)
                     :client_socket(socket), client_id(otherSender.client_id),
                      notifications_queue(otherSender.notifications_queue),
                      nick_names(otherSender.nick_names) {
}

void ClientHandlersSender::popFromQueueAndSendInstruction() {
    std::shared_ptr<Instruction> instruc_ptr;
    this->notifications_queue.pop(instruc_ptr);
    ServerProtocol protocol;
    protocol.sendPacketWithUpdates(this->client_socket, instruc_ptr, this->nick_names, this->client_id);
}

void ClientHandlersSender::run() {
    try {
        while (true)
            this->popFromQueueAndSendInstruction();
    }
    catch(const BlockingQueueClosed & e) {
        std::cout << "me cachie" << std::endl;
    }
}