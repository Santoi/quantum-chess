#include "server.h"
#include "matches_repository.h"
#include <iostream>

#define MAX_CLIENTS 10

Server::Server(const char* host, const char* service)
        :acceptor_socket(std::move(Socket::createAListeningSocket(host, service))) {
}

void Server::executeAcceptorThread() {
    //MatchesRepository matches;
    while (true) {
        try {
            //matches.acceptSingleThreadedClientAndAddToAMatch(this->acceptor_socket);
            return;
        } catch (...) {
            //joinearHilosClientes(hilos_clientes);
            return;
        }

    }
}


void Server::executeSingleThreadedServer() {
    MatchesRepository matches;
    for (int i = 0; i < MAX_CLIENTS; i++)
        matches.acceptSingleThreadedClientAndAddToAMatch(this->acceptor_socket);
}

void Server::executeServerWithThreads() {
    std::thread acceptor_thread(&Server::executeAcceptorThread, this);
    while (std::cin.get() != 'q') {
    }
    this->acceptor_socket.stopAccepting();
    acceptor_thread.join();
}

void Server::execute(bool one_thread_only) {
    if (one_thread_only)
        this->executeSingleThreadedServer();
    else
        this->executeServerWithThreads();
}

