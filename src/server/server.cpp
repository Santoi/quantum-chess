#include "server.h"
#include "communication/match_organizer.h"
#include "communication/acceptor_thread.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

#define BOARDS_PATH "boards/"

Server::Server(const char *host, const char *service)
        : acceptor_socket(Socket::createAListeningSocket(host, service)) {
}

void Server::execute(const std::string &filename) {
  std::string filename_ = BOARDS_PATH + filename;
  std::ifstream file(filename_);
  if (!file.is_open())
    throw std::invalid_argument("file doesnt exist");
  MatchOrganizer matches(file);
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

