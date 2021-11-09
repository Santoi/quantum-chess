#include <iostream>

#include "client.h"

Client::Client(const char* host, const char* servidor)
        :client_socket(std::move(Socket::createAConnectedSocket(host, servidor))),
         protocol(), is_active(true) {
}

void Client::readFromStandardInput(std::string& message) {
    std::getline(std::cin, message);
    //std::cin >> message;
}

void Client::makeAction(const std::string& message) {
    if (message == "exit") {
        std::cout<< "exiting" <<std::endl;
        this->is_active = false;
    } else {
        this->protocol.sendMessage(this->client_socket, message);
    }
}

void Client::readFromStandardInputAndMakeAction() {
    std::cout << "Escriba un mensaje para el chat" << std::endl;
    std::string message;
    readFromStandardInput(message);
    makeAction(message);
}

void Client::receiveMessage() {
    if (!this->is_active)
        return;
    std::string message;
    this->protocol.receiveInstruction(this->client_socket, message);
    std::cout << message << std::endl;
}

int Client::getAndPrintNumberOfAvailableGames() {
    int max_games = this->protocol.receiveNumberOfRunningGames(this->client_socket);
    std::cout << "Bienvenido a Quantum Chess. Selecciona de las partidas disponibles a cuál de estas"
                 " quieres entrar." << std::endl;
    std::cout << "Los números de partida disponibles son los siguientes: " << std::endl;
    for (int i = 0; i < max_games; i++)
        std::cout << i << ", " << std::endl;
    std::cout << "¿Quieres crear una nueva partida? Escribe entonces " << max_games << std::endl;
    std::cout << "Escriba un número de partida: " << std::endl;
    return max_games;
}

void Client::askForMatchNumber(const int& max_games) {
    int game_number;
    do {
        std::cin >> game_number;
    } while ((game_number < 0) || game_number > max_games);
    this->protocol.sendChosenGame(this->client_socket, game_number);
    std::string aux;
    std::getline(std::cin, aux); //empty cin buffer
}

void Client::associateClientWithARunningMatch() {
    int max_games = this->getAndPrintNumberOfAvailableGames();
    askForMatchNumber(max_games);
}

void Client::execute() {
    this->associateClientWithARunningMatch();
    while (this->is_active) {
        this->readFromStandardInputAndMakeAction();
        this->receiveMessage();
    }
}