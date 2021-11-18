#include "matches_repository.h"
#include "server_protocol.h"
#include <algorithm>
#include "../../common/src/unique_ptr.h"

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
        if ((*it)->hasActiveClients())
            return true;
    }
    return false;
}


void MatchesRepository::joinInactiveMatches() {
    for (auto it = ptr_matches.begin(); it != ptr_matches.end(); ){
        if (!(*it)->hasActiveClients()) {
            (*it)->stop();
            (*it)->join();
            it = ptr_matches.erase(it);
            continue;
        }
        ++it;
    }
}

void MatchesRepository::acceptClientAndAddToAMatch(Socket& acceptor_socket, bool threaded_match) {
    int match_number;
    Socket client_socket = this->acceptClientAndGetClientChosenMatch(acceptor_socket, match_number, threaded_match);
    ptr_matches[match_number]->addClientToMatch(std::move(client_socket),
                                                threaded_match);
}

void MatchesRepository::addClientToMatchCreatingIfNeeded(Socket&& client_socket, bool threaded_match) {
    int chosen_match = getClientChosenMatch(client_socket, true);
    ptr_matches[chosen_match]->addClientToMatch(std::move(client_socket),
                                                threaded_match);
}

void MatchesRepository::stopMatches() {
    for (auto & match: ptr_matches) {
        std::cout << "detengo esta match" << std::endl;
        match->stop();
    }
}

void MatchesRepository::joinMatches() {
    for (auto & match: ptr_matches) {
        std::cout << "joineo el match" << std::endl;
        match->join();
    }
}

