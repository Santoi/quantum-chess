#include "matches_map.h"

MatchesMap::MatchesMap() : created_matches(0), accepted_clients(0), map(),
                           mutex() {}

uint16_t MatchesMap::addNewMatchAndStart(std::ifstream &file) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  map.insert(std::make_pair((created_matches), Match(file)));
  map.at(created_matches).start();
  return created_matches++;
}

void MatchesMap::addNewClientToMatch(uint16_t match_id, Socket &&socket) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  map.at(match_id).addClientToMatch(std::move(socket), accepted_clients++);
}

bool MatchesMap::matchExists(uint16_t match_id) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return map.count(match_id);
}

void
MatchesMap::getMatchesData(
        std::map<uint16_t, std::vector<ClientData>> &data) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  for (auto &match: map)
    data.insert(std::make_pair(match.first, match.second.getClientsData()));
}

void MatchesMap::stopMatches() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  for (auto &match: map) {
    match.second.stop();
  }
}

void MatchesMap::joinMatches() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  for (auto &match: map)
    match.second.join();
}

void MatchesMap::joinInactiveMatches() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  for (auto it = map.begin(); it != map.end();) {
    if (!it->second.hasActiveClients()) {
      it->second.stop();
      it->second.join();
      it = map.erase(it);
      continue;
    }
    ++it;
  }
}
