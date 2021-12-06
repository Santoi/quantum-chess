#include "matches_repository.h"
#include "server_protocol.h"
#include <algorithm>
#include "../../common/src/unique_ptr.h"

MatchOrganizer::MatchOrganizer(std::ifstream &file_)
        : matches_map(), file(file_) {
}

// TODO HACER LO DE REFRESH
uint16_t MatchOrganizer::getClientChosenMatch(Socket &client_socket) {
  ServerProtocol protocol;
  std::map<uint16_t, std::vector<ClientData>> matches_data;
  matches_map.getMatchesData(matches_data);
  protocol.sendMatchesInfo(client_socket, matches_data);
  uint16_t match_number = protocol.receiveChosenGame(client_socket);
  return match_number;
}

void MatchOrganizer::joinInactiveMatches() {
  matches_map.joinInactiveMatches();
}

void
MatchOrganizer::addClientToMatchCreatingIfNeeded(Socket &&client_socket) {
  uint16_t match_id = getClientChosenMatch(client_socket);
  if (!matches_map.matchExists(match_id)) {
    match_id = matches_map.addNewMatchAndStart(file);
  }
  matches_map.addNewClientToMatch(match_id,
                                  std::move(client_socket));
}

void MatchOrganizer::stopMatches() {
  matches_map.stopMatches();
}

void MatchOrganizer::joinMatches() {
  matches_map.joinMatches();
}


