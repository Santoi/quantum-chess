#ifndef QUANTUM_CHESS_PROJ_MATCHES_REPOSITORY_H
#define QUANTUM_CHESS_PROJ_MATCHES_REPOSITORY_H

#include <vector>
#include "match.h"
#include "../../common/src/socket.h"
#include <memory>

class MatchesRepository {
private:
  uint16_t created_matches;
  std::map<uint16_t, std::unique_ptr<Match>> ptr_matches;
  uint16_t accepted_clients;

public:
  //Creates a MatchesRepository, setting the number of created_matches equal to cero.
  MatchesRepository();

  //Iterates over the matches vector: if any of them is active, a true is returned. If
  //none of them is active, a false is returned.
  bool thereAreActiveMatches();

  //Iterates over the matches vector: if a match is inactive, the method pushExitInstructionToUpdatesQueue
  //is called over the match to force its termination, and after that the match thread is joined.
  void joinInactiveMatches();

  ~MatchesRepository() = default;

  void stopMatches();

  void
  addClientToMatchCreatingIfNeeded(Socket &&client_socket);

  void joinMatches();

private:
  //Creates a new match and increases the created_matches number by one.
  uint16_t createNewMatch();

  //Following the protocol, it sends the number of games running to the remote client,
  //and receives the client's chosen game. If the client wants to play in a new match, a new match
  //is created.
  uint16_t getClientChosenMatch(Socket &client_socket);
};

#endif //QUANTUM_CHESS_PROJ_MATCHES_REPOSITORY_H
