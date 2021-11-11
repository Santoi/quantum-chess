#ifndef QUANTUM_CHESS_PROJ_SERVER_PROTOCOL_H
#define QUANTUM_CHESS_PROJ_SERVER_PROTOCOL_H

#include "common_socket.h"
#include "common_packet.h"
#include "instructions.h"
#include "nick_names_repository.h"
#include "protocol.h"
#include <memory>
#include "protocol.h"

class Instruction;


class ServerProtocol: public Protocol {

public:
    ServerProtocol() = default;
    void sendNumberOfGamesRunning(Socket& socket, const int& max_games);
    int receiveNumberOfChosenGame(Socket& socket);
    void getNickName(Socket& socket, std::string& nick_name);
    void fillInstructionsWithPacket(Socket& socket, const int& client_id, std::shared_ptr<Instruction>& instruct_ptr);
    void sendPacketWithUpdates(Socket& socket, std::shared_ptr<Instruction>& instruct_ptr, const NickNamesRepository& nick_names);
    void fillPacketWithChatInfo(Packet& packet, std::string&& nick_name, std::string&& message);
    ~ServerProtocol() = default;

private:
    void fillChatInstructionsWithPacket(Socket& socket, const int& client_id, std::shared_ptr<Instruction>& instruct_ptr);

    void fillMovementInstructionsWithPacket(Socket& socket, const int& client_id, std::shared_ptr<Instruction>& instruct_ptr);
};


#endif //QUANTUM_CHESS_PROJ_SERVER_PROTOCOL_H
