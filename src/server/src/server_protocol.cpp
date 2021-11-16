#include "server_protocol.h"
#include "../../common/src/packet.h"
#include "instructions/instruction.h"
#include "instructions/chat_instruction.h"
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
    return (int)(this->getNumber16FromSocket(socket));
}

void ServerProtocol::getNickName(Socket& socket, std::string& nick_name) {
    this->getMessageFromSocket(socket, nick_name);
}

void ServerProtocol::fillChatInstructions(Socket& socket, const int& client_id,
                                                std::shared_ptr<Instruction>& instruct_ptr) {
    std::string message;
    this->getMessageFromSocket(socket, message);
    instruct_ptr = std::make_shared<ChatInstruction>(client_id, std::move(message));
}

void ServerProtocol::fillMovementInstructions(Socket& socket, const int& client_it ,
                                                        std::shared_ptr<Instruction>& instruct_ptr) {

}

void ServerProtocol::fillInstructions(Socket& socket, const int& client_id,
                                                std::shared_ptr<Instruction>& instruct_ptr) {
    Packet packet;
    socket.receive(packet, ONE_BYTE);
    char action = packet.getByte();
    if (action == 'c')
        fillChatInstructions(socket, client_id, instruct_ptr);
    else
        fillMovementInstructions(socket, client_id, instruct_ptr);
}

void ServerProtocol::fillPacketWithChatInfo(Packet& packet, const std::string& nick_name, const std::string& message) {
    packet.addByte('c');
    this->addStringAndItsLengthToPacket(packet, nick_name);
    this->addStringAndItsLengthToPacket(packet, message);
}

void ServerProtocol::fillPacketWithLoadBoardInfo(Packet & packet, const std::vector<char> & characters, const std::vector<Position> & positions) {
    packet.addByte('l');
    packet.addByte(characters.size());
    for (uint16_t i = 0; i < characters.size(); i++) {
        packet.addByte(characters[i]);
        packet.addByte(positions[i].x());
        packet.addByte(positions[i].y());
    }
}

void ServerProtocol::sendPacketWithUpdates(Socket& socket, std::shared_ptr<Instruction>& instruct_ptr,
                                           const NickNamesRepository& nick_names, const int& client_id) {
    Packet packet;
    instruct_ptr->fillPacketWithInstructionsToSend(*this, packet, nick_names, client_id);
    socket.send(packet);
}

void ServerProtocol::fillPacketWithExitInfo(Packet& packet, const std::string& nick_name) {
    packet.addByte('e');
    this->addStringAndItsLengthToPacket(packet, nick_name);
}


