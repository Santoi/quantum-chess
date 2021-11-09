#include <iostream>

#include "client.h"

Client::Client(const char* host, const char* servidor)
        :client_socket(std::move(Socket::createConnectedSocket(host, servidor))),
         protocol(), is_active(true) {
}

void Client::readFromStandardInput(std::string& message) {
    std::getline(std::cin, message);
}

void Client::makeAction(const std::string& message) {
    if (message == "exit") {
        this->is_active = false;
    } else {
        this->protocol.sendMessage(this->client_socket, message);
    }
}

void Client::readFromStandardInputAndMakeAction() {
    std::string message;
    readFromStandardInput(message);
    makeAction(message);
}

void Client::receiveMessage() {
    if (!this->is_active)
        return;
}

void Client::execute() {
    while (this->is_active) {
        this->readFromStandardInputAndMakeAction();
        this->receiveMessage();
    }
}