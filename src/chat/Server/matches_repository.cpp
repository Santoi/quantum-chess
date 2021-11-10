#include "matches_repository.h"
#include "server_protocol.h"

MatchesRepository::MatchesRepository()
                    :active_matches(0) {
}

void MatchesRepository::createNewMatch() {
    //create new game
    Match new_match;
    //add to vector of match
    this->matches.push_back(std::move(new_match));
    //create new thread for new game
    //match[active_matches].start()
    this->active_matches++;
}

int MatchesRepository::getClientChosenMatch(Socket& client_socket) {
    ServerProtocol protocol;
    protocol.sendNumberOfGamesRunning(client_socket, this->active_matches);
    int match_number = protocol.receiveNumberOfChosenGame(client_socket);
    if (match_number <= this->active_matches)
        this->createNewMatch();
    return match_number;
}

void MatchesRepository::acceptSingleThreadedClientAndAddToAMatch(Socket& acceptor_socket) {
    Socket client_socket = acceptor_socket.acceptSocket();
    int match_number = getClientChosenMatch(client_socket);
    matches[match_number].addSingleThreadedClientToMatchAndStart(std::move(client_socket));
}
/*
void MatchesRepository::acceptClientAndAddToAMatch(Socket& acceptor_socket) {
    Socket client_socket;
    this->addClientToAMatch(acceptor_socket, client_socket);
    matches[match_number].addClientToMatchAndStartItsThread(std::move(client_socket));

    //it->startSingleThreadedClient(matches[match_number]);
}*/


