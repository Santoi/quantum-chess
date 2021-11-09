#include "client_handler.h"
#include "common_packet.h"
#include "instructions.h"

#define MAX_MESSAGES 10

ClientHandler::ClientHandler(Socket&& socket)
                :client_socket(std::move(socket)) {
}

ClientHandler::ClientHandler(ClientHandler&& other_client)
                :client_socket(std::move(other_client.client_socket)),
                 notifications_queue(other_client.notifications_queue),
                 updates_queue(other_client.updates_queue),
                 receiver_thread(std::move(other_client.receiver_thread)),
                 sender_thread(std::move(other_client.sender_thread)) {

}


int ClientHandler::chooseGame(const int& max_games) {
    this->protocol.sendNumberOfGamesRunning(this->client_socket, max_games);
    return (this->protocol.receiveNumberOfChosenGame(this->client_socket));
}

void ClientHandler::executeReceiver() {
    std::shared_ptr<Instruction> ptr_instruction;
    this->protocol.fillPacketWithInstructions(this->client_socket, ptr_instruction);
    this->updates_queue->push(ptr_instruction);
}

void ClientHandler::executeReceiverCatchingExceptions() {
    this->executeReceiver();
}

void ClientHandler::executeSender() {
    std::shared_ptr<Instruction> instruc_ptr;
    this->notifications_queue->pop(instruc_ptr);
    this->protocol.sendPacketWithUpdates(this->client_socket, instruc_ptr);
}

void ClientHandler::executeSenderCatchingExceptions() {
    this->executeSender();
}


void ClientHandler::start() {
    this->receiver_thread = std::thread(&ClientHandler::executeReceiverCatchingExceptions, this);
    this->sender_thread = std::thread(&ClientHandler::executeSenderCatchingExceptions, this);
}

void ClientHandler::startSingleThreadedClient(Match& match) {
    for (int i = 0; i < MAX_MESSAGES; i++) {
        this->executeReceiverCatchingExceptions();
        match.checkAndNotifyUpdates();
        this->executeSenderCatchingExceptions();
    }
}

