#include "common_packet.h"
#include <unistd.h>
#include <arpa/inet.h>

#include "client_protocol.h"

#define ONE_BYTE 1
#define TWO_BYTES 2

int ClientProtocol::receiveNumberOfRunningGames(Socket& socket) {
    return (int)(this->getNumberFromSocket(socket));
}

void ClientProtocol::sendChosenGame(Socket& socket, const int& game_number) {
    Packet packet;
    this->changeNumberToBigEndianAndAddToPacket(packet, (uint16_t)game_number);
    socket.send(packet);
}

void ClientProtocol::sendClientsNickName(Socket& socket, std::string& nick_name) {
    Packet packet;
    this->addStringAndItsLengthToPacket(packet, nick_name);
    socket.send(packet);
}

void ClientProtocol::sendChatMessage(Socket& socket, const std::string& message) {
    Packet packet;
    packet.addByte('c');
    this->addStringAndItsLengthToPacket(packet, message);
    socket.send(packet);
}

void ClientProtocol::receiveInstruction(Socket& socket, std::string& nick_name, std::string& message) {
    Packet packet;
    socket.receive(packet, ONE_BYTE);
    this->getMessageFromSocket(socket, nick_name);
    this->getMessageFromSocket(socket, message);
}


