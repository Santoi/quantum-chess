#include <iostream>
#include "client.h"
#include "client_protocol.h"

Client::Client(const char* host, const char* servidor)
        :client_socket(std::move(Socket::createAConnectedSocket(host, servidor))),
        received(), send(),
         remote_sender(client_socket), remote_receiver(client_socket, received),
         board() {
}


void Client::readFromStandardInput(std::string& message) {
    std::getline(std::cin, message);
}

int Client::getAndPrintNumberOfAvailableGames() {
    ClientProtocol protocol;
    int max_games = protocol.receiveNumberOfRunningGames(this->client_socket);
    std::cout << "Selecciona de las partidas disponibles a cuál de estas"
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
    ClientProtocol protocol;
    protocol.sendChosenGame(this->client_socket, game_number);
    std::string aux;
    std::getline(std::cin, aux); //empty cin buffer
}

void Client::associateClientWithARunningMatch() {
    int max_games = this->getAndPrintNumberOfAvailableGames();
    askForMatchNumber(max_games);
}

void Client::welcomeClientAndAskForNickName() {
    std::cout << "Bienvenido a Quantum Chess. Por favor, ingresá tu nombre para "
                 "comenzar a jugar." << std::endl;
    this->readFromStandardInput(this->clients_nick_name);
    std::cout << "¡Qué tal, " << this->clients_nick_name << "! ¿Listo para jugar?" << std::endl;
}

void Client::setUpClientsDataInServer() {
    this->welcomeClientAndAskForNickName();
    this->associateClientWithARunningMatch();
    ClientProtocol protocol;
    protocol.sendClientsNickName(this->client_socket, this->clients_nick_name);
}

void Client::executeSingleThreadedClient() {
    while (true) {
        this->remote_sender.readFromStandardInputAndMakeAction();
        this->remote_receiver.receiveMessage();
    }
}

void Client::executeThreadedClient() {
    this->remote_sender.start();
    this->remote_receiver.start();
    while (true) {
        std::shared_ptr<RemoteClientInstruction> ptr_instruction;
        received.pop(ptr_instruction);
        ptr_instruction->makeAction(board);
    }
    this->remote_sender.join();
    this->remote_receiver.join();
}

void Client::execute(bool single_threaded_client) {
    this->setUpClientsDataInServer();
    if (single_threaded_client)
        this->executeSingleThreadedClient();
    else
        this->executeThreadedClient();
}