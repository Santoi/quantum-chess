#include "client_handler.h"
#include "../../common/src/packet.h"
#include "instructions/instruction.h"
#include "../../common/src/socket_closed.h"


ClientHandler::ClientHandler(Socket&& socket, BlockingQueue<Instruction>& notifications_queue, BlockingQueue<Instruction>&
                              updates_queue, const ClientData & client_data_)
              :client_socket(std::move(socket)), notifications_queue(notifications_queue),
              client_data(client_data_), client_is_active(true),
               client_receiver(client_socket, client_data, updates_queue),
               client_sender(client_socket, notifications_queue, client_data) {
}

ClientHandler::ClientHandler(ClientHandler&& other_client)
                :client_socket(std::move(other_client.client_socket)),
                notifications_queue(other_client.notifications_queue), client_data(other_client.client_data),
                client_is_active(other_client.client_is_active),
                 client_receiver(std::move(other_client.client_receiver), client_socket),
                 client_sender(std::move(other_client.client_sender), client_socket) {
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
    this->client_receiver.join();
    this->client_sender.join();
    //client_is_active = false;
}

const ClientData &ClientHandler::getData() const {
    return client_data;
}
