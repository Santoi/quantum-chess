#include "server_protocol.h"
#include "common_packet.h"
#include "instructions.h"
#include <unistd.h>
#include <arpa/inet.h>

#define ONE_BYTE 1
#define TWO_BYTES 2


void ServerProtocol::sendNumberOfGamesRunning(Socket& socket, const int& max_games) {
    Packet packet;
    changeNumberToBigEndianAndAddToPacket(packet, (uint16_t)max_games);
    socket.send(packet);
}

int ServerProtocol::receiveNumberOfChosenGame(Socket& socket) {
    return (int)(this->getLittleEndianNumberFromSocket(socket));
}

void ServerProtocol::getNickName(Socket& socket, std::string& nick_name) {
    this->getMessageFromSocket(socket, nick_name);
}

void ServerProtocol::fillChatInstructionsWithPacket(Socket& socket, const int& client_id,
                                                std::shared_ptr<Instruction>& instruct_ptr) {
    std::string message;
    this->getMessageFromSocket(socket, message);
    instruct_ptr = std::make_shared<ChatInstruction>(client_id, std::move(message));
}

void ServerProtocol::fillMovementInstructionsWithPacket(Socket& socket, const int& client_it ,
                                                        std::shared_ptr<Instruction>& instruct_ptr) {

}

void ServerProtocol::fillInstructionsWithPacket(Socket& socket, const int& client_id,
                                                std::shared_ptr<Instruction>& instruct_ptr) {
    Packet packet;
    socket.receive(packet, ONE_BYTE);
    char action = packet.getByte();
    if (action == 'c')
        fillChatInstructionsWithPacket(socket, client_id, instruct_ptr);
    else
        fillMovementInstructionsWithPacket(socket, client_id, instruct_ptr);
}

void ServerProtocol::fillPacketWithChatInfo(Packet& packet, const std::string& nick_name, const std::string& message) {
    packet.addByte('c');
    this->addStringAndItsLengthToPacket(packet, nick_name);
    this->addStringAndItsLengthToPacket(packet, message);
}

void ServerProtocol::sendPacketWithUpdates(Socket& socket, std::shared_ptr<Instruction>& instruct_ptr,
                                           const NickNamesRepository& nick_names) {
    Packet packet;
    instruct_ptr->fillPacketWithInstructionsToSend(*this, packet, nick_names);
    socket.send(packet);
}

