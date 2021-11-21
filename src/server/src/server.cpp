#include "server.h"
#include "matches_repository.h"
#include "acceptor_thread.h"
#include <iostream>
#include <chrono>
#include <thread>

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
    if (type_of_single_thread == SINGLE_THREADED_MATCH_AND_CLIENTS){
        for (int i = 0; i < MAX_CLIENTS; i++)
            matches.acceptSingleThreadedClientAndAddToAMatch(this->acceptor_socket);
    }
    else if (type_of_single_thread == SINGLE_THREADED_MATCH_AND_THREADED_CLIENTS) {
        for (int i = 0; i < MAX_CLIENTS; i++)
            matches.acceptClientAndAddToAMatch(this->acceptor_socket, false);
    }
    else if (type_of_single_thread == THREADED_MATCH_AND_THREADED_CLIENTS) {
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
    MatchesRepository matches;
    AcceptorThread acceptor_thread(acceptor_socket, matches);
    acceptor_thread.start();
    while (true) {
        std::string input;
        std::cin >> input;
        if (input == "q")
            break;
    }
    acceptor_socket.shutdownAndClose();
    acceptor_thread.join();
}

void Server::execute(bool one_thread_only, int type_of_single_thread) {
    if (one_thread_only)
        this->executeSingleThreadedServer(type_of_single_thread);
    else
        this->executeServerWithThreads();
}

