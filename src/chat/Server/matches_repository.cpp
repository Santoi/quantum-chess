#include "matches_repository.h"
#include "server_protocol.h"
#include <algorithm>
#include "unique_ptr.h"

MatchesRepository::MatchesRepository()
                    :created_matches(0) {
}

void MatchesRepository::createNewMatch(bool threaded_match) {
    std::unique_ptr<Match> new_match_ptr = make_unique<Match>();
    this->ptr_matches.push_back(std::move(new_match_ptr));
    if (threaded_match)
        this->ptr_matches[this->created_matches]->start();
    this->created_matches++;
}

int MatchesRepository::getClientChosenMatch(Socket& client_socket, bool threaded_match) {
    ServerProtocol protocol;
    protocol.sendNumberOfGamesRunning(client_socket, this->created_matches);
    int match_number = protocol.receiveNumberOfChosenGame(client_socket);
    if (match_number == this->created_matches)
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
    ptr_matches[match_number]->addSingleThreadedClientToMatchAndStart(std::move(client_socket));
}

bool MatchesRepository::thereAreActiveMatches() {
    std::vector<std::unique_ptr<Match>>::iterator it;
    for (it = this->ptr_matches.begin(); it != this->ptr_matches.end(); it++){
        if ((*it)->isActive())
            return true;
    }
    return false;
}

bool isInactive(const std::unique_ptr<Match>& match_ptr) {
    return (!match_ptr->isActive());
}

void MatchesRepository::deleteInactiveMatchesFromList() {
    this->ptr_matches.erase(std::remove_if(ptr_matches.begin(), ptr_matches.end(), isInactive), ptr_matches.end());
}


void MatchesRepository::joinInactiveMatches() {
    std::vector<std::unique_ptr<Match>>::iterator it;
    for (it = this->ptr_matches.begin(); it != this->ptr_matches.end(); it++){
        if ((*it)->isJoinable()){
            (*it)->pushExitInstructionToUpdatesQueue();
            (*it)->join();
        }
    }
    this->deleteInactiveMatchesFromList();
}

void MatchesRepository::acceptClientAndAddToAMatch(Socket& acceptor_socket, bool threaded_match) {
    int match_number;
    Socket client_socket = this->acceptClientAndGetClientChosenMatch(acceptor_socket, match_number, threaded_match);
    ptr_matches[match_number]->addClientToMatchAndStart(std::move(client_socket), threaded_match);
}


