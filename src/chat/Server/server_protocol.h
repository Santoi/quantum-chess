#ifndef QUANTUM_CHESS_PROJ_SERVER_PROTOCOL_H
#define QUANTUM_CHESS_PROJ_SERVER_PROTOCOL_H

#include "common_socket.h"

class ServerProtocol {

public:
    ServerProtocol() = default;
    void sendNumberOfGamesRunning(Socket& socket, const int& max_games);
    int receiveNumberOfChosenGame(Socket& socket);
    ~ServerProtocol() = default;
};


#endif //QUANTUM_CHESS_PROJ_SERVER_PROTOCOL_H
