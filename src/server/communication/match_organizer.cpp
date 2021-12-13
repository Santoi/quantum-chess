#include "match_organizer.h"
#include "server_protocol.h"
#include <algorithm>
#include "../../common/unique_ptr.h"
#include <map>
#include <vector>

#define REFRESH UINT16_MAX

MatchOrganizer::MatchOrganizer(std::ifstream &file_)
    : matches_map(), file(file_) {
}

uint16_t MatchOrganizer::getClientChosenMatch(Socket &client_socket) {
  ServerProtocol protocol;
  uint16_t match_number = 0;
  // Sends data, if client sends REFRESH (UINT16_MAX) then data is sent again.
  do {
    std::map<uint16_t, std::vector<ClientData>> matches_data;
    matches_map.getMatchesData(matches_data);
    protocol.sendMatchesInfo(client_socket, matches_data);
    match_number = protocol.receiveChosenGame(client_socket);
  } while (match_number == REFRESH);
  return match_number;
}

void MatchOrganizer::joinInactiveMatches() {
  matches_map.joinInactiveMatches();
}

void
MatchOrganizer::addClientToMatchCreatingIfNeeded(Socket &&client_socket) {
  uint16_t match_id = getClientChosenMatch(client_socket);
  if (match_id == 0)
    match_id = matches_map.addNewMatchAndStart(file);
  if (!matches_map.matchExists(match_id))
    throw std::runtime_error("match doesnt exists");
  matches_map.addNewClientToMatch(match_id,
                                  std::move(client_socket));
}

void MatchOrganizer::stopMatches() {
  matches_map.stopMatches();
}

void MatchOrganizer::joinMatches() {
  matches_map.joinMatches();
}


