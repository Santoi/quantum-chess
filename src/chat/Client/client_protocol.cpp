#include "common_packet.h"
#include <unistd.h>
#include <arpa/inet.h>
#include "unique_ptr.h"
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

void ClientProtocol::fillClientInstructionWithChat(Socket& socket, std::unique_ptr<RemoteClientInstruction>&
                                                                    ptr_instruction) {
    std::string nick_name;
    std::string message;
    this->getMessageFromSocket(socket, nick_name);
    this->getMessageFromSocket(socket, message);
    ptr_instruction = make_unique<RemoteClientChatInstruction>(nick_name, message);

}

void ClientProtocol::fillClientInstructionWithExitMessage(Socket& socket, std::unique_ptr<RemoteClientInstruction>&
                                                                            ptr_instruction) {
    std::string nick_name;
    this->getMessageFromSocket(socket, nick_name);
    ptr_instruction = make_unique<RemoteClientExitMessageInstruction>(nick_name);
}

void ClientProtocol::receiveInstruction(Socket& socket, std::unique_ptr<RemoteClientInstruction>&
                                                        ptr_instruction) {
    Packet packet;
    socket.receive(packet, ONE_BYTE);
    char action = packet.getByte();
    if (action == 'c')
        this->fillClientInstructionWithChat(socket, ptr_instruction);
    else if (action == 'e')
        this->fillClientInstructionWithExitMessage(socket, ptr_instruction);

}


