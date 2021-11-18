#include "client_handler.h"
#include "../../common/src/packet.h"
#include "instructions/instruction.h"
#include "../../common/src/socket_closed.h"


ClientHandler::ClientHandler(Socket&& socket, BlockingQueue<Instruction>& notifications_queue, BlockingQueue<Instruction>&
                              updates_queue, const int& client_id, const NickNamesRepository& nick_names)
              :client_socket(std::move(socket)), notifications_queue(notifications_queue), client_is_active(true),
               client_receiver(client_socket, client_id, updates_queue),
               client_sender(client_socket, notifications_queue, client_id, nick_names) {
}

ClientHandler::ClientHandler(ClientHandler&& other_client)
                :client_socket(std::move(other_client.client_socket)),
                notifications_queue(other_client.notifications_queue), client_is_active(other_client.client_is_active),
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

void ClientHandler::startSingleThreadedClient(Match& match) {
    /*
    try {
        while (true) {
            this->client_receiver.receiveInstructionAndPushToQueue();
            match.checkAndNotifyUpdates();
            this->client_sender.popFromQueueAndSendInstruction();
        }
    }
    catch(const SocketClosed& error) {
        try{
            this->client_receiver.pushToQueueExitInstruction();
            match.checkAndNotifyUpdates();
            this->client_sender.popFromQueueAndSendInstruction();
        }
        catch(const std::exception & e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        catch(...){
            std::cerr << "Error desconocido" << std::endl;
        }
        this->client_is_active = false;

    }
    catch(const std::exception & e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch(...){
        std::cerr << "Error desconocido" << std::endl;
    }*/
}

void ClientHandler::startThreadedClient(Match& match, bool threaded_match) {
    client_receiver.start();
    client_sender.start();
}

bool ClientHandler::isActive() const {
    return client_is_active;
}

void ClientHandler::stop() {
    client_socket.shutdownAndClose();
    notifications_queue.close();
}

void ClientHandler::join() {
    std::cout << "joineo el recibidor" << std::endl;
    this->client_receiver.join();
    std::cout << "joineo sender" << std::endl;
    this->client_sender.join();
    //client_is_active = false;
    std::cout << "joinee todo" << std::endl;
}
