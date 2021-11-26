#include "server.h"
#include "matches_repository.h"
#include "acceptor_thread.h"
#include <iostream>
#include <chrono>
#include <thread>

Server::Server(const char *host, const char *service)
        : acceptor_socket(
        std::move(Socket::createAListeningSocket(host, service))) {
}

void Server::execute() {
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

