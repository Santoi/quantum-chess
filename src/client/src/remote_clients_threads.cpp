#include "remote_clients_threads.h"
#include "client_protocol.h"
#include <iostream>
#include "remote_client_instructions.h"
#include "../../common/src/blocking_queue.h"
#include "../../common/src/socket_closed.h"

RemoteClientSender::RemoteClientSender(Socket& client_socket, BlockingQueue<RemoteClientInstruction> & send_queue_)
                    :client_socket(client_socket), send_queue(send_queue_) {
}

void RemoteClientSender::readFromStandardInput(std::string& message) {
    std::getline(std::cin, message);
}
/*
void RemoteClientSender::makeAction(const std::string& message) {
    if (message == "exit") {
        std::cout<< "exiting" <<std::endl;
        this->client_socket.stopCommunication();
        this->sender_is_active = false;
    } else {

        protocol.sendChatMessage(this->client_socket, message);
    }
}*/

void RemoteClientSender::readFromStandardInputAndMakeAction() {
    std::string message;
    this->readFromStandardInput(message);
    //this->makeAction(message);
}

void RemoteClientSender::run() {
    ClientProtocol protocol;
    try {
        while (true) {
            std::shared_ptr<RemoteClientInstruction> instruction;
            send_queue.pop(instruction);
            protocol.sendInstruction(client_socket, instruction);
        }
    }
    catch (const BlockingQueueClosed &e) {}
}


RemoteClientReceiver::RemoteClientReceiver(Socket& client_socket,
                                           BlockingQueue<RemoteClientInstruction> & queue_)
                    :client_socket(client_socket), queue(queue_) {}

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
    catch (const SocketClosed & e) {
        std::cerr << "Error: se perdio conexion con el server" << std::endl;
    }
}