#include "server.h"
#include "matches_repository.h"
#include <iostream>
#include <chrono>
#include <thread>



#define MAX_CLIENTS 3

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

void Server::executeSingleThreadedServer(int type_of_single_thread) {
    MatchesRepository matches;
    if (type_of_single_thread == 1){
        for (int i = 0; i < MAX_CLIENTS; i++)
            matches.acceptSingleThreadedClientAndAddToAMatch(this->acceptor_socket);
    }
    else if (type_of_single_thread == 2) {
        for (int i = 0; i < MAX_CLIENTS; i++)
            matches.acceptClientAndAddToAMatch(this->acceptor_socket, false);
    }
    else if (type_of_single_thread == 3) {
        for (int i = 0; i < MAX_CLIENTS; i++)
            matches.acceptClientAndAddToAMatch(this->acceptor_socket, true);
    }
    while (matches.thereAreActiveMatches()){
        matches.joinInactiveMatches();
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    }
    matches.joinInactiveMatches();
}

void Server::executeServerWithThreads() {
    std::thread acceptor_thread(&Server::executeAcceptorThread, this);
    while (std::cin.get() != 'q') {
    }
    this->acceptor_socket.stopAccepting();
    acceptor_thread.join();
}

void Server::execute(bool one_thread_only, int type_of_single_thread) {
    if (one_thread_only)
        this->executeSingleThreadedServer(type_of_single_thread);
    else
        this->executeServerWithThreads();
}

