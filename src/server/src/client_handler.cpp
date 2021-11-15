#include "client_handler.h"
#include "../../common/src/packet.h"
#include "instructions/instruction.h"
#include "../../common/src/socket_closed.h"


ClientHandler::ClientHandler(Socket&& socket, BlockingQueue& notifications_queue, ThreadSafeQueue&
                              updates_queue, const int& client_id, const NickNamesRepository& nick_names)
              :client_socket(std::move(socket)),
               client_receiver(client_socket, client_id, updates_queue),
               client_sender(client_socket, notifications_queue, client_id, nick_names),
               client_is_active(true) {
}

ClientHandler::ClientHandler(ClientHandler&& other_client)
                :client_socket(std::move(other_client.client_socket)),
                 client_receiver(std::move(other_client.client_receiver), client_socket),
                 client_sender(std::move(other_client.client_sender), client_socket),
                 client_is_active(other_client.client_is_active) {
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
    try {
        while (true) {
            this->client_receiver.receiveInstructionAndPushToQueue();
            match.checkAndNotifyUpdates();
            this->client_sender.popFromQueueAndSendInstruction();
        }
    } catch (const SocketClosed& error) {
        this->client_receiver.pushToQueueExitInstruction();
        match.checkAndNotifyUpdates();
        try {
            this->client_sender.popFromQueueAndSendInstruction();
        } catch (...) {
            this->client_is_active = false;
        }
    } catch (...) {
    }
}

void ClientHandler::startThreadedClient(Match& match, bool threaded_match) {
    this->start();
    if (!threaded_match){
        while (client_is_active)
            match.checkAndNotifyUpdates();
    }
}

bool ClientHandler::isActive() const {
    return client_is_active;
}

void ClientHandler::join() {
    if (this->client_receiver.isJoinable())
        this->client_receiver.join();
    if (this->client_sender.isJoinable())
        this->client_sender.join();
    client_is_active = false;
}
