#include "server.h"

Server::Server(const char* host, const char* service)
        :acceptor_socket(std::move(Socket::createAListeningSocket(host, service))) {
}

void Server::executeSingleThreadedServer() {

}

void Server::executeServerWithThreads() {

}

void Server::execute(bool one_thread_only) {
    if (one_thread_only)
        this->executeSingleThreadedServer();
    else
        this->executeServerWithThreads();
}

