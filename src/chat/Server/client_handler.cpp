#include "client_handler.h"
#include "common_packet.h"
#include "instructions.h"

#define MAX_MESSAGES 10

ClientHandler::ClientHandler(Socket&& socket, BlockingQueue& notifications_queue, ThreadSafeQueue&
                              updates_queue, const int& client_id, const NickNamesRepository& nick_names)
              :client_socket(std::move(socket)),
               client_receiver(client_socket, client_id, updates_queue),
               client_sender(client_socket, notifications_queue, nick_names) {
}


ClientHandler::ClientHandler(ClientHandler&& other_client)
                :client_socket(std::move(other_client.client_socket)),
                 client_receiver(std::move(other_client.client_receiver), client_socket),
                 client_sender(std::move(other_client.client_sender), client_socket) {
}


int ClientHandler::chooseGame(const int& max_games) {
    ServerProtocol protocol;
    protocol.sendNumberOfGamesRunning(this->client_socket, max_games);
    return (protocol.receiveNumberOfChosenGame(this->client_socket));
}


void ClientHandler::getClientsNickName(std::string& nick_name) {
    ServerProtocol protocol;
    protocol.getNickName(client_socket, nick_name);
}

void ClientHandler::start() {
    this->client_receiver.start();
    this->client_sender.start();
}


void ClientHandler::startSingleThreadedClient(Match& match) {
    for (int i = 0; i < MAX_MESSAGES; i++) {
       this->client_receiver.runCatchingExceptions();
       match.checkAndNotifyUpdates();
       this->client_sender.runCatchingExceptions();
    }
}

void ClientHandler::startThreadedClientWithoutMatchThread(Match& match) {
    this->start();
    for (int i = 0; i < MAX_MESSAGES; i++)
        match.checkAndNotifyUpdates();
}
