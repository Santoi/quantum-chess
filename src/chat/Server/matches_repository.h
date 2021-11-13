#ifndef QUANTUM_CHESS_PROJ_MATCHES_REPOSITORY_H
#define QUANTUM_CHESS_PROJ_MATCHES_REPOSITORY_H

#include <vector>
#include "match.h"
#include "common_socket.h"

class MatchesRepository {
private:
    int active_matches;
    std::vector<Match> matches;

public:
    MatchesRepository();
    //void createAndAcceptClientAndAddToAMatch(Socket& acceptor_socket);
    void acceptSingleThreadedClientAndAddToAMatch(Socket& acceptor_socket);
    void acceptClientAndAddToAMatch(Socket& acceptor_socket, bool threaded_match);
    bool thereAreActiveMatches();
    void joinInactiveMatches();
    ~MatchesRepository() = default;

private:
    Socket acceptClientAndGetClientChosenMatch(Socket& acceptor_socket, int& match_number, bool threaded_match);
    int getClientChosenMatch(Socket& client_socket, bool threaded_match);
    void createNewMatch(bool threaded_match);
    void deleteInactiveMatchesFromList();
};



#endif //QUANTUM_CHESS_PROJ_MATCHES_REPOSITORY_H
