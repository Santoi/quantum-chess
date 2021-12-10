#ifndef QUANTUM_CHESS_PROJ_MATCHES_MAP_H
#define QUANTUM_CHESS_PROJ_MATCHES_MAP_H

#include <cstdint>
#include <map>
#include "match.h"

// Protected class that stores matches.
class MatchesMap {
  uint16_t next_match_id;
  uint16_t accepted_clients;
  std::map<uint16_t, Match> map;
  std::mutex mutex;

public:
  MatchesMap();

  // Adds a new match and start its thread. Returns id of new match.
  uint16_t addNewMatchAndStart(std::ifstream &file);

  // Loads map with vectors with data of clients of different matches.
  void getMatchesData(std::map<uint16_t, std::vector<ClientData>> &data);

  // Joins threads of matches ended.
  void joinInactiveMatches();

  // Creates (and starts it threads) a client and add it to match corresponding
  // to match id.
  void addNewClientToMatch(uint16_t match_id, Socket &&socket);

  // Returns true if match with match id exists.
  bool matchExists(uint16_t match_id);

  // Stops all matches.
  void stopMatches();

  // Joins all matches.
  void joinMatches();
};


#endif //QUANTUM_CHESS_PROJ_MATCHES_MAP_H
