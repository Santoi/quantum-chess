#ifndef QUANTUM_CHESS_PROJ_SERVER_PROTOCOL_H
#define QUANTUM_CHESS_PROJ_SERVER_PROTOCOL_H

#include "common_socket.h"
#include "common_packet.h"
#include "instructions.h"
#include "nick_names_repository.h"
#include "server_protocol.h"
#include <memory>

class Instruction;

class ServerProtocol {

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

    void changeNumberToBigEndianAndAddToPacket(Packet& packet, const uint16_t& number);

    uint16_t getLittleEndianNumberFromSocket(Socket& socket);

    void getMessageOfSizeFomSocket(Socket& socket, std::string& message, const int& size_of_word);

    void addStringAndItsLengthToPacket(Packet& packet, std::string&& string);
};


#endif //QUANTUM_CHESS_PROJ_SERVER_PROTOCOL_H
