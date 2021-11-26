#include "matches_repository.h"
#include "server_protocol.h"
#include <algorithm>
#include "../../common/src/unique_ptr.h"

MatchesRepository::MatchesRepository()
        : created_matches(0), ptr_matches(), accepted_clients(0) {
}

uint16_t MatchesRepository::createNewMatch() {
  std::unique_ptr<Match> new_match_ptr = make_unique<Match>();
  ptr_matches.insert(
          std::make_pair(created_matches, std::move(new_match_ptr)));
  ptr_matches[this->created_matches]->start();
  return created_matches++;
}

uint16_t MatchesRepository::getClientChosenMatch(Socket &client_socket) {
  ServerProtocol protocol;
  protocol.sendMatchesInfo(client_socket, ptr_matches);
  uint16_t match_number = protocol.receiveChosenGame(client_socket);
  return match_number;
}

bool MatchesRepository::thereAreActiveMatches() {
  for (auto it = ptr_matches.begin(); it != ptr_matches.end(); it++) {
    if (it->second->hasActiveClients())
      return true;
  }
  return false;
}


void MatchesRepository::joinInactiveMatches() {
  for (auto it = ptr_matches.begin(); it != ptr_matches.end();) {
    if (!it->second->hasActiveClients()) {
      it->second->stop();
      it->second->join();
      it = ptr_matches.erase(it);
      continue;
    }
    ++it;
  }
}

void
MatchesRepository::addClientToMatchCreatingIfNeeded(Socket &&client_socket) {
  uint16_t match = getClientChosenMatch(client_socket);
  if (!ptr_matches.count(match))
    match = createNewMatch();
  ptr_matches[match]->addClientToMatch(std::move(client_socket),
                                       accepted_clients);
  accepted_clients++;
}

void MatchesRepository::stopMatches() {
  for (auto &match: ptr_matches) {
    match.second->stop();
  }
}

void MatchesRepository::joinMatches() {
  for (auto &match: ptr_matches)
    match.second->join();
}


