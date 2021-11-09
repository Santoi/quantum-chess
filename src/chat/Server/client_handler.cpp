#include "client_handler.h"

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


int ClientHandler::chooseGame() {
    return 0;
}

