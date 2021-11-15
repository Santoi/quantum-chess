#ifndef QUANTUM_CHESS_PROJ_MATCHES_REPOSITORY_H
#define QUANTUM_CHESS_PROJ_MATCHES_REPOSITORY_H

#include <vector>
#include "match.h"
#include "common_socket.h"
#include <memory>

class MatchesRepository {
private:
    int created_matches;
    std::vector<std::unique_ptr<Match>> ptr_matches;

public:
    //Creates a MatchesRepository, setting the number of created_matches equal to cero.
    MatchesRepository();

    //Accepts a new remote client, tells them what games are available to play/observe,
    //and receives client's chosen game. If client wants to create a new match, a new match
    //is created and added to the list of matches. Then, the corresponding match is asked
    //to start single threaded client (and therefore a single threaded match).
    void acceptSingleThreadedClientAndAddToAMatch(Socket& acceptor_socket);

    //Accepts a new remote client, tells them what games are available to play/observe,
    //and receives client's chosen game. If client wants to create a new match, a new match
    //is created and added to the list of matches. Then, the corresponding match is asked
    //to start with threads if threaded_match is true, else a single_threaded match is
    //started.
    void acceptClientAndAddToAMatch(Socket& acceptor_socket, bool threaded_match);

    //Iterates over the matches vector: if any of them is active, a true is returned. If
    //none of them is active, a false is returned.
    bool thereAreActiveMatches();

    //Iterates over the matches vector: if a match is inactive, the method pushExitInstructionToUpdatesQueue
    //is called over the match to force its termination, and after that the match thread is joined.
    void joinInactiveMatches();

    ~MatchesRepository() = default;

private:
    //Accepts the new remote client using the acceptor_socket. It gets the client's chosen match
    //and creates the match if necessary. The remote client socket is returned.
    Socket acceptClientAndGetClientChosenMatch(Socket& acceptor_socket, int& match_number, bool threaded_match);

    //Following the protocol, it sends the number of games running to the remote client,
    //and receives the client's chosen game. If the client wants to play in a new match, a new match
    //is created (using the boolean threaded_match).
    int getClientChosenMatch(Socket& client_socket, bool threaded_match);

    //Creates a new match and increases the created_matches number by one. If the boolean
    //threaded_match is true, then the new match is asked to start execution.
    void createNewMatch(bool threaded_match);

    //Deletes from matches vector the matches that are not active.
    void deleteInactiveMatchesFromList();
};

#endif //QUANTUM_CHESS_PROJ_MATCHES_REPOSITORY_H
