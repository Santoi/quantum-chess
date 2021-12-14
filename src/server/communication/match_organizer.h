#ifndef QUANTUM_CHESS_PROJ_MATCH_ORGANIZER_H
#define QUANTUM_CHESS_PROJ_MATCH_ORGANIZER_H

#include <vector>
#include "match.h"
#include "../../common/socket.h"
#include "matches_map.h"
#include <memory>

class MatchOrganizer {
private:
  MatchesMap matches_map;
  std::ifstream &file;

public:
  explicit MatchOrganizer(std::ifstream &file_);

  // Joins all matches that are inactive.
  void joinInactiveMatches();

  ~MatchOrganizer() = default;

  // Stops all matches.
  void stopMatches();

  // Add client, ask it for match and add it to match, creating if doesn't
  // exist the selected one.
  void
  addClientToMatchCreatingIfNeeded(Socket &&client_socket);

  // Join all matches.
  void joinMatches();

private:
  // Sends matches information to client and receive the chosen one.
  uint16_t getClientChosenMatch(const Socket &client_socket);
};

#endif //QUANTUM_CHESS_PROJ_MATCH_ORGANIZER_H
