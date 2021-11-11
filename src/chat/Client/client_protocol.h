#ifndef QUANTUM_CHESS_PROJ_CLIENT_PROTOCOL_H
#define QUANTUM_CHESS_PROJ_CLIENT_PROTOCOL_H

#include <string>
#include "common_socket.h"
#include "protocol.h"

class ClientProtocol: public Protocol {
public:
    ClientProtocol() = default;
    int receiveNumberOfRunningGames(Socket& socket);
    void sendChosenGame(Socket& socket, const int& game_number);
    void sendClientsNickName(Socket& socket, std::string& nick_name);
    void sendChatMessage(Socket& socket, const std::string& message);
    void receiveInstruction(Socket& socket, std::string& nick_name, std::string& message);
    ~ClientProtocol() = default;
};

#endif //QUANTUM_CHESS_PROJ_CLIENT_PROTOCOL_H
