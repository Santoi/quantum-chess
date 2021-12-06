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
  //Creates a MatchOrganizer, setting the number of created_matches equal to cero.
  explicit MatchOrganizer(std::ifstream &file_);

  //Iterates over the matches vector: if a match is inactive, the method pushExitInstructionToUpdatesQueue
  //is called over the match to force its termination, and after that the match thread is joined.
  void joinInactiveMatches();

  ~MatchOrganizer() = default;

  void stopMatches();

  void
  addClientToMatchCreatingIfNeeded(Socket &&client_socket);

  void joinMatches();

private:
  //Following the protocol, it sends the number of games running to the remote client,
  //and receives the client's chosen game. If the client wants to play in a new match, a new match
  //is created.
  uint16_t getClientChosenMatch(Socket &client_socket);
};

#endif //QUANTUM_CHESS_PROJ_MATCHES_REPOSITORY_H
