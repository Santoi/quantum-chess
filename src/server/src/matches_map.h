#ifndef QUANTUM_CHESS_PROJ_MATCHES_MAP_H
#define QUANTUM_CHESS_PROJ_MATCHES_MAP_H

#include <cstdint>
#include <map>
#include "match.h"

class MatchesMap {
  uint16_t created_matches;
  uint16_t accepted_clients;
  std::map<uint16_t, Match> map;
  std::mutex mutex;

public:
  MatchesMap();

  uint16_t addNewMatchAndStart(std::ifstream &file);

  void getMatchesData(std::map<uint16_t, std::vector<ClientData>> &data);

  void joinInactiveMatches();

  void addNewClientToMatch(uint16_t match_id, Socket &&socket);

  bool matchExists(uint16_t match_id);

  void stopMatches();

  void joinMatches();
};


#endif //QUANTUM_CHESS_PROJ_MATCHES_MAP_H
