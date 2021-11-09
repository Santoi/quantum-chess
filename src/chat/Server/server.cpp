#include "server.h"
#include <iostream>

#define MAX_CLIENTS 10

Server::Server(const char* host, const char* service)
        :acceptor_socket(std::move(Socket::createAListeningSocket(host, service))) {
}

void Server::createClientAndAddToList(std::list<ClientHandler>& clients) {
    Socket client_socket = this->acceptor_socket.acceptSocket();
    ClientHandler client(std::move(client_socket));
    clients.push_back(std::move(client));
}

void Server::executeAcceptorThread() {
    std::list<ClientHandler> clients;
    std::list<ClientHandler>::iterator it = clients.begin();
    std::vector<Match> match;
    int active_matches = 0;
    while (true) {
        try {
            this->createClientAndAddToList(clients);
        } catch (...) {
            //joinearHilosClientes(hilos_clientes);
            return;
        }
        ++it;
        int match_number = it->chooseGame(active_matches);
        if (match_number <= active_matches) {
            //create new game
            Match new_match;
            //add to vector of match
            match.push_back(std::move(new_match));
            //create new thread for new game
            //match[active_matches].start()
            active_matches++;
        }
        match[match_number].addClientToQueues(*it);
      //  it->start();
    }
}


void Server::executeSingleThreadedServer() {
    std::list<ClientHandler> clients;
    std::list<ClientHandler>::iterator it = clients.begin();
    std::vector<Match> match;
    int active_matches = 0;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        this->createClientAndAddToList(clients);
        ++it;
        int match_number = it->chooseGame(active_matches);
        if (match_number <= active_matches) {
            //create new game
            Match new_match;
            //add to vector of match
            match.push_back(std::move(new_match));
            //create new thread for new game
            //match[active_matches].start()
            active_matches++;
        }
        match[match_number].addClientToQueues(*it);
        //  it->start();
    }
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

