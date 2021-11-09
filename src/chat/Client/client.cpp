#include <iostream>

#include "client.h"

Client::Client(const char* host, const char* servidor)
        :client_socket(std::move(Socket::crearSocketClienteYConectarlo(host, servidor))),
         protocol(), is_active(true) {
}

void Client::readFromStandardInputAndMakeAction() {
    std::string message;
    std::getline(std::cin, message);

}

void Client::receiveMessage() {

}

void Client::execute() {
    while (this->is_active) {
        this->readFromStandardInputAndMakeAction();
        this->receiveMessage();
    }
}