#include "remote_clients_threads.h"
#include "client_protocol.h"
#include <iostream>
#include "remote_client_instructions.h"

RemoteClientSender::RemoteClientSender(Socket& client_socket)
                    :client_socket(client_socket) {
}

void RemoteClientSender::readFromStandardInput(std::string& message) {
    std::getline(std::cin, message);
}

void RemoteClientSender::makeAction(const std::string& message) {
    if (message == "exit") {
        std::cout<< "exiting" <<std::endl;
        this->client_socket.stopCommunication();
        this->sender_is_active = false;
    } else {
        ClientProtocol protocol;
        protocol.sendChatMessage(this->client_socket, message);
    }
}

void RemoteClientSender::readFromStandardInputAndMakeAction() {
    std::string message;
    this->readFromStandardInput(message);
    this->makeAction(message);
}

void RemoteClientSender::run() {
    std::cout << "Escriba mensajes para el chat" << std::endl;
    while (this->sender_is_active)
        this->readFromStandardInputAndMakeAction();
}


RemoteClientReceiver::RemoteClientReceiver(Socket& client_socket)
                    :client_socket(client_socket) {
}

void RemoteClientReceiver::receiveMessage() {
    std::unique_ptr<RemoteClientInstruction> ptr_instruction;
    ClientProtocol protocol;
    protocol.receiveInstruction(this->client_socket, ptr_instruction);
    ptr_instruction->makeAction();
}

void RemoteClientReceiver::run() {
    while (true)
        this->receiveMessage();
}