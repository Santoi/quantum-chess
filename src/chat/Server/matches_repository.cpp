#include "matches_repository.h"
#include "server_protocol.h"

MatchesRepository::MatchesRepository()
                    :active_matches(0) {
}

void MatchesRepository::createNewMatch(bool threaded_match) {
    //create new game
    Match new_match;
    //add to vector of match
    this->matches.push_back(std::move(new_match));
    if (threaded_match)
        new_match.start();
    //create new thread for new game
    this->active_matches++;
}

int MatchesRepository::getClientChosenMatch(Socket& client_socket, bool threaded_match) {
    ServerProtocol protocol;
    protocol.sendNumberOfGamesRunning(client_socket, this->active_matches);
    int match_number = protocol.receiveNumberOfChosenGame(client_socket);
    if (match_number <= this->active_matches)
        this->createNewMatch(threaded_match);
    return match_number;
}

Socket MatchesRepository::acceptClientAndGetClientChosenMatch(Socket& acceptor_socket, int& match_number,
                                                              bool threaded_match) {
    Socket client_socket = acceptor_socket.acceptSocket();
    match_number = getClientChosenMatch(client_socket, threaded_match);
    return client_socket;
}

void MatchesRepository::acceptSingleThreadedClientAndAddToAMatch(Socket& acceptor_socket) {
    int match_number;
    Socket client_socket = this->acceptClientAndGetClientChosenMatch(acceptor_socket, match_number, false);
    matches[match_number].addSingleThreadedClientToMatchAndStart(std::move(client_socket));
}

bool MatchesRepository::thereAreActiveMatches() {
    std::vector<Match>::iterator it;
    for (it = this->matches.begin(); it != this->matches.end(); it++){
        if (it->isActive())
            return true;
    }
    return false;
}


void MatchesRepository::deleteInactiveMatchesFromList() {

}


void MatchesRepository::joinInactiveMatches() {
    std::vector<Match>::iterator it;
    for (it = this->matches.begin(); it != this->matches.end(); it++){
        if (!(it->isActive()))
            it->join();
    }
    this->deleteInactiveMatchesFromList();
}

void MatchesRepository::acceptClientAndAddToAMatch(Socket& acceptor_socket, bool threaded_match) {
    int match_number;
    Socket client_socket = this->acceptClientAndGetClientChosenMatch(acceptor_socket, match_number, threaded_match);
    matches[match_number].addClientToMatchAndStart(std::move(client_socket));
}


/*
void MatchesRepository::acceptClientAndAddToAMatch(Socket& acceptor_socket) {
    Socket client_socket;
    this->addClientToAMatch(acceptor_socket, client_socket);
    matches[match_number].addClientToMatchAndStartItsThread(std::move(client_socket));

    //it->startSingleThreadedClient(matches[match_number]);
}*/


