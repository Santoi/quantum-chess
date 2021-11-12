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
    void acceptClientAndAddToAMatch(Socket& acceptor_socket);
    ~MatchesRepository() = default;

private:
    Socket acceptClientAndGetClientChosenMatch(Socket& acceptor_socket, int& match_number);
    int getClientChosenMatch(Socket& client_socket);
    void createNewMatch();

};



#endif //QUANTUM_CHESS_PROJ_MATCHES_REPOSITORY_H
