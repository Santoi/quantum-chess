#ifndef QUANTUM_CHESS_PROJ_MATCHES_REPOSITORY_H
#define QUANTUM_CHESS_PROJ_MATCHES_REPOSITORY_H

#include <vector>
#include "match.h"
#include "../../common/src/socket.h"
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
  uint16_t getClientChosenMatch(Socket &client_socket);
};

#endif //QUANTUM_CHESS_PROJ_MATCHES_REPOSITORY_H
