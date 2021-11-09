#ifndef QUANTUM_CHESS_PROJ_CLIENT_PROTOCOL_H
#define QUANTUM_CHESS_PROJ_CLIENT_PROTOCOL_H

#include <string>
#include "common_socket.h"

class ClientProtocol {
public:
    ClientProtocol() = default;
    int receiveNumberOfRunningGames(Socket& socket);
    void sendChosenGame(Socket& socket, const int& game_number);
    void sendMessage(Socket& socket, const std::string& message);
    ~ClientProtocol() = default;
};

#endif //QUANTUM_CHESS_PROJ_CLIENT_PROTOCOL_H