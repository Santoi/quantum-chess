#include "server.h"

Server::Server(const char* host, const char* service)
        :acceptor_socket(std::move(Socket::createAListeningSocket(host, service))) {
}

void Server::agregarClienteALista(std::list<ManejaCliente>& hilos_clientes) {
    Socket socket_cliente = this->socket_aceptador.aceptarSocket();
    ManejaCliente cliente(std::move(socket_cliente), this->protocolo, this->mapa_colas);
    hilos_clientes.push_back(std::move(cliente));
}

void Server::executeAcceptorThread() {
    std::list<ManejaCliente> clients_threads;
    std::list<ManejaCliente>::iterator it = clients_threads.begin();
    std::vector<Game> games;
    int games_counter = 0;
    while (true) {
        try {
            this->agregarClienteALista(hilos_clientes);
        } catch (const NoSePuedeAceptarSocketError& error) {
            joinearHilosClientes(hilos_clientes);
            return;
        }
        ++it;
        int game_number = it->chooseGame();
        if (game_number <= game_counter) {
            //create new game
            //create new thread for new game
            //add to vector of games
        }
        it->start();
    }
}


void Server::executeSingleThreadedServer() {

}

void Server::executeServerWithThreads() {
    std::thread acceptor_thread(&Server::executeAcceptorThread, this);
    while (std::cin.get() != 'q') {
    }
    this->acceptor_socket.stopAccepting();
    hilo_aceptador.join();
}

void Server::execute(bool one_thread_only) {
    if (one_thread_only)
        this->executeSingleThreadedServer();
    else
        this->executeServerWithThreads();
}

