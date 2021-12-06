#ifndef QUANTUM_CHESS_PROJ_MATCHES_MAP_H
#define QUANTUM_CHESS_PROJ_MATCHES_MAP_H

#include <cstdint>
#include <map>
#include "match.h"

class MatchesMap {
  std::map<uint16_t, Match> map;
  std::mutex mutex;

public:
  MatchesMap();

  void addNewMatch(uint16_t match_id, std::ifstream &file);

  void startMatch(uint16_t match_id);

  void getMatchesData(std::map<uint16_t, std::vector<ClientData>> &data);

  void joinInactiveMatches();

  void addNewClientToMatch(uint16_t match_id, uint16_t client_id,
                           Socket &&socket);

  bool matchExists(uint16_t match_id);

  void stopMatches();

  void joinMatches();
};


#endif //QUANTUM_CHESS_PROJ_MATCHES_MAP_H
