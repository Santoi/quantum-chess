#ifndef QUANTUM_CHESS_PROJ_SERVER_PROTOCOL_H
#define QUANTUM_CHESS_PROJ_SERVER_PROTOCOL_H

#include "common_socket.h"
#include "common_packet.h"
#include "instructions.h"
#include <memory>

class ServerProtocol {

public:
    ServerProtocol() = default;
    void sendNumberOfGamesRunning(Socket& socket, const int& max_games);
    int receiveNumberOfChosenGame(Socket& socket);
    void getNickName(Socket& socket, std::string& nick_name);
    void fillPacketWithInstructions(Socket& socket, std::shared_ptr<Instruction>& instruct_ptr);
    void sendPacketWithUpdates(Socket& socket, std::shared_ptr<Instruction>& instruct_ptr);
    ~ServerProtocol() = default;

private:
    void fillPacketWithChatInstructions(Socket& socket, std::shared_ptr<Instruction>& instruct_ptr);

    void fillPacketWithMovementInstructions(Socket& socket, std::shared_ptr<Instruction>& instruct_ptr);
};


#endif //QUANTUM_CHESS_PROJ_SERVER_PROTOCOL_H
