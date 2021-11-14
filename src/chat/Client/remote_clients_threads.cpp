#include "remote_clients_threads.h"
#include "client_protocol.h"
#include <iostream>
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
    } else {
        ClientProtocol protocol;
        protocol.sendChatMessage(this->client_socket, message);
    }
}

void RemoteClientSender::readFromStandardInputAndMakeAction() {
    std::cout << "Escriba un mensaje para el chat" << std::endl;
    std::string message;
    this->readFromStandardInput(message);
    this->makeAction(message);
}

void RemoteClientSender::run() {
    while (this->sender_is_active)
        this->readFromStandardInputAndMakeAction();
}
