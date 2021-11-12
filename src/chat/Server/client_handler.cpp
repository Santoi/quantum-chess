#include "client_handler.h"
#include "common_packet.h"
#include "instructions.h"

#define MAX_MESSAGES 10

ClientHandler::ClientHandler(Socket&& socket, BlockingQueue& notifications_queue, ThreadSafeQueue&
                              updates_queue, const int& client_id, const NickNamesRepository& nick_names)
              :client_socket(std::move(socket)),
              client_receiver(client_socket, client_id, updates_queue),
              client_id(client_id), nick_names(nick_names),
              notifications_queue(notifications_queue), updates_queue(updates_queue) {
}


ClientHandler::ClientHandler(ClientHandler&& other_client)
                :client_socket(std::move(other_client.client_socket)),
                 client_receiver(std::move(other_client.client_receiver), client_socket),
                 client_id(other_client.client_id),
                 nick_names(other_client.nick_names), notifications_queue(other_client.notifications_queue),
                 updates_queue(other_client.updates_queue),
                 receiver_thread(std::move(other_client.receiver_thread)),
                 sender_thread(std::move(other_client.sender_thread)) {

}


int ClientHandler::chooseGame(const int& max_games) {
    this->protocol.sendNumberOfGamesRunning(this->client_socket, max_games);
    return (this->protocol.receiveNumberOfChosenGame(this->client_socket));
}


void ClientHandler::getClientsNickName(std::string& nick_name) {
    this->protocol.getNickName(client_socket, nick_name);
}

void ClientHandler::executeReceiver() {
    std::shared_ptr<Instruction> ptr_instruction;
    this->protocol.fillInstructionsWithPacket(this->client_socket, this->client_id, ptr_instruction);
    this->updates_queue.push(ptr_instruction);
}

void ClientHandler::executeReceiverCatchingExceptions() {
    this->executeReceiver();
}

void ClientHandler::executeSender() {
    std::shared_ptr<Instruction> instruc_ptr;
    this->notifications_queue.pop(instruc_ptr);
    this->protocol.sendPacketWithUpdates(this->client_socket, instruc_ptr, this->nick_names);
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
       // this->client_receiver.runCatchingExceptions();
       this->executeReceiverCatchingExceptions();
       match.checkAndNotifyUpdates();
        this->executeSenderCatchingExceptions();
    }
}

