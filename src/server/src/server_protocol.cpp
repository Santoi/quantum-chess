#include "server_protocol.h"
#include "../../common/src/packet.h"
#include "instructions/instruction.h"
#include "instructions/chat_instruction.h"
#include "instructions/movement_instruction.h"
#include "match.h"
#include "../../common/src/client_data.h"
#include <unistd.h>
#include <arpa/inet.h>

#define ONE_BYTE 1
#define TWO_BYTES 2


void ServerProtocol::sendMatchesInfo(Socket& socket, const std::map<uint16_t, std::unique_ptr<Match>> & matches) {
    Packet packet;
    changeNumberToBigEndianAndAddToPacket(packet, matches.size());
    for (auto & pair: matches){
        changeNumberToBigEndianAndAddToPacket(packet, (uint16_t) pair.first);
        std::vector<const ClientData *> client_data_repository =
                                                pair.second->getClientsData();
        changeNumberToBigEndianAndAddToPacket(packet, (uint16_t) client_data_repository.size());
        for (auto & client_data: client_data_repository) {
            changeNumberToBigEndianAndAddToPacket(packet, (uint16_t) client_data->getId());
            addStringAndItsLengthToPacket(packet, client_data->getName());
            addNumber8ToPacket(packet, client_data->isPlayer());
        }
    }
    socket.send(packet);
}

uint16_t ServerProtocol::receiveNumberOfChosenGame(Socket& socket) {
    return (uint16_t)(this->getNumber16FromSocket(socket));
}

void ServerProtocol::getNickName(Socket& socket, std::string& nick_name) {
    this->getMessageFromSocket(socket, nick_name);
}

void ServerProtocol::fillChatInstructions(Socket& socket, const ClientData &client_data,
                                          std::shared_ptr<Instruction>& instruct_ptr) {
    std::string message;
    this->getMessageFromSocket(socket, message);
    instruct_ptr = std::make_shared<ChatInstruction>(client_data, std::move(message));
}

void ServerProtocol::fillMovementInstructions(Socket& socket, const ClientData &client_data ,
                                              std::shared_ptr<Instruction>& instruct_ptr) {
    uint8_t ix = getNumber8FromSocket(socket);
    uint8_t iy = getNumber8FromSocket(socket);
    uint8_t fx = getNumber8FromSocket(socket);
    uint8_t fy = getNumber8FromSocket(socket);
    Position initial(ix, iy);
    Position final(fx, fy);
    instruct_ptr = std::make_shared<MovementInstruction>(client_data, initial, final);
}

void ServerProtocol::fillInstructions(Socket& socket, const ClientData &client_data,
                                      std::shared_ptr<Instruction>& instruct_ptr) {
    Packet packet;
    socket.receive(packet, ONE_BYTE);
    char action = packet.getByte();

    switch (action) {
        case 'c':
            fillChatInstructions(socket, client_data, instruct_ptr);
            break;
        case 'm':
            fillMovementInstructions(socket, client_data, instruct_ptr);
            break;
    }
}

void ServerProtocol::fillPacketWithChatInfo(Packet& packet, const std::string& nick_name, const std::string& message) {
    packet.addByte('c');
    this->addStringAndItsLengthToPacket(packet, nick_name);
    this->addStringAndItsLengthToPacket(packet, message);
}

void ServerProtocol::fillPacketWithLoadBoardInfo(Packet &packet,
                                                 const std::vector<char> &characters,
                                                 const std::vector<bool> &colors,
                                                 const std::vector<Position> &positions,
                                                 const std::vector<double> &probabilities) {
    packet.addByte('l');
    packet.addByte(characters.size());
    for (uint16_t i = 0; i < characters.size(); i++) {
        packet.addByte(characters[i]);
        packet.addByte(colors[i]);
        packet.addByte(positions[i].x());
        packet.addByte(positions[i].y());
        uint16_t prob_int = probabilities[i] * (UINT16_MAX + 1) - 1;
      changeNumberToBigEndianAndAddToPacket(packet, prob_int);
    }
}

void ServerProtocol::sendPacketWithUpdates(Socket &socket,
                                           std::shared_ptr<Instruction> &instruct_ptr,
                                           const ClientData &client_data) {
    Packet packet;
    instruct_ptr->fillPacketWithInstructionsToSend(*this, packet, client_data);
    socket.send(packet);
}

void ServerProtocol::fillPacketWithExitInfo(Packet& packet, const std::string& nick_name) {
    packet.addByte('e');
    this->addStringAndItsLengthToPacket(packet, nick_name);
}


