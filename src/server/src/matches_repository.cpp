#include "matches_repository.h"
#include "server_protocol.h"
#include <algorithm>
#include "../../common/src/unique_ptr.h"

MatchesRepository::MatchesRepository(std::ifstream &file_)
        : created_matches(0), accepted_clients(0), matches_map(),
          file(file_) {
}

// TODO HACER LO DE REFRESH
uint16_t MatchesRepository::getClientChosenMatch(Socket &client_socket) {
  ServerProtocol protocol;
  std::map<uint16_t, std::vector<ClientData>> matches_data;
  matches_map.getMatchesData(matches_data);
  protocol.sendMatchesInfo(client_socket, matches_data);
  uint16_t match_number = protocol.receiveChosenGame(client_socket);
  return match_number;
}

void MatchesRepository::joinInactiveMatches() {
  matches_map.joinInactiveMatches();
}

void
MatchesRepository::addClientToMatchCreatingIfNeeded(Socket &&client_socket) {
  uint16_t match_id = getClientChosenMatch(client_socket);
  if (!matches_map.matchExists(match_id)) {
    matches_map.addNewMatch(created_matches, file);
    matches_map.startMatch(created_matches);
    match_id = created_matches;
    created_matches++;
  }
  matches_map.addNewClientToMatch(match_id, accepted_clients++,
                                  std::move(client_socket));
}

void MatchesRepository::stopMatches() {
  matches_map.stopMatches();
}

void MatchesRepository::joinMatches() {
  matches_map.joinMatches();
}


