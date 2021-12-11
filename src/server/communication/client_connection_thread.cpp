#include "client_connection_thread.h"

ClientConnectionThread::ClientConnectionThread(Socket &&socket_,
                                               MatchOrganizer &matches_)
        : socket(std::move(socket_)), matches(matches_), active(true) {
}


bool ClientConnectionThread::isActive() const {
  return active;
}

void ClientConnectionThread::stop() {
  socket.shutdownAndClose();
  active = false;
}

void ClientConnectionThread::run() {
  matches.addClientToMatchCreatingIfNeeded(std::move(socket));
  active = false;
}
