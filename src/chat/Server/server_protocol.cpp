#include "server_protocol.h"
#include "common_packet.h"
#include "instructions.h"
#include <unistd.h>
#include <arpa/inet.h>

#define ONE_BYTE 1
#define TWO_BYTES 2


void ServerProtocol::changeNumberToBigEndianAndAddToPacket(Packet& packet, const uint16_t& number) {
    uint16_t numberBE = htons(number);
    packet.addBytes(numberBE);
}


void ServerProtocol::sendNumberOfGamesRunning(Socket& socket, const int& max_games) {
    Packet packet;
    changeNumberToBigEndianAndAddToPacket(packet, (uint16_t)max_games);
    socket.send(packet);
}


int ServerProtocol::receiveNumberOfChosenGame(Socket& socket) {
    Packet packet;
    socket.receive(packet, TWO_BYTES);
    uint16_t game_numberBE;
    packet.getBytes(game_numberBE);
    return (int)(ntohs(game_numberBE));
}

void ServerProtocol::getNickName(Socket& socket, std::string& nick_name) {
    Packet packet;
    socket.receive(packet, TWO_BYTES);
    uint16_t size_of_wordBE;
    packet.getBytes(size_of_wordBE);
    uint16_t size_of_word = ntohs(size_of_wordBE);
    socket.receive(packet, size_of_word);
    packet.getBytes(nick_name, size_of_word);
}


void ServerProtocol::fillChatInstructionsWithPacket(Socket& socket, const int& client_id,
                                                std::shared_ptr<Instruction>& instruct_ptr) {
    Packet packet;
    socket.receive(packet, TWO_BYTES);
    uint16_t size_of_wordBE;
    packet.getBytes(size_of_wordBE);
    uint16_t size_of_word = ntohs(size_of_wordBE);
    socket.receive(packet, size_of_word);
    std::string message;
    packet.getBytes(message, size_of_word);
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

void ServerProtocol::addStringAndItsLengthToPacket(Packet& packet, std::string&& string) {
    uint16_t host_length = string.size();
    this->changeNumberToBigEndianAndAddToPacket(packet, host_length);
    packet.addBytes(string);
}


void ServerProtocol::fillPacketWithChatInfo(Packet& packet, std::string&& nick_name, std::string&& message) {
    packet.addByte('c');
    this->addStringAndItsLengthToPacket(packet, std::move(nick_name));
    this->addStringAndItsLengthToPacket(packet, std::move(message));
}



void ServerProtocol::sendPacketWithUpdates(Socket& socket, std::shared_ptr<Instruction>& instruct_ptr,
                                           const NickNamesRepository& nick_names) {
    Packet packet;
    instruct_ptr->fillPacketWithInstructionsToSend(*this, packet, nick_names);
    socket.send(packet);
}

