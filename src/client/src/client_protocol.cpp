#include "../../common/src/packet.h"
#include <unistd.h>
#include <arpa/inet.h>
#include "../../common/src/unique_ptr.h"
#include "client_protocol.h"

#define ONE_BYTE 1
#define TWO_BYTES 2

int ClientProtocol::receiveNumberOfRunningGames(Socket& socket) {
    return (int)(this->getNumber16FromSocket(socket));
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

void ClientProtocol::fillClientInstructionWithChat(Socket& socket, std::shared_ptr<RemoteClientInstruction>&
                                                                    ptr_instruction) {
    std::string nick_name;
    std::string message;
    this->getMessageFromSocket(socket, nick_name);
    this->getMessageFromSocket(socket, message);
    ptr_instruction = make_unique<RemoteClientChatInstruction>(nick_name, message);

}

void ClientProtocol::fillClientInstructionWithExitMessage(Socket& socket, std::shared_ptr<RemoteClientInstruction>&
                                                                            ptr_instruction) {
    std::string nick_name;
    this->getMessageFromSocket(socket, nick_name);
    ptr_instruction = make_unique<RemoteClientExitMessageInstruction>(nick_name);
}

void ClientProtocol::fillClientInstructionWithLoadBoard(Socket& socket, std::shared_ptr<RemoteClientInstruction>&
ptr_instruction) {
    // TODO mejorar el protocolo con otros datos.
    uint8_t amount = getNumber8FromSocket(socket);
    std::vector<char> characters;
    std::vector<Position> positions;
    positions.reserve(amount);
    characters.reserve(amount);
    for (uint8_t i = 0; i < amount; i++) {
        characters.push_back(getCharFromSocket(socket));
        Position position(getNumber8FromSocket(socket), getNumber8FromSocket(socket));
        positions.push_back(position);
    }
    ptr_instruction = make_unique<RemoteClientLoadMessageInstruction>(std::move(characters), std::move(positions));
}

void ClientProtocol::receiveInstruction(Socket& socket, std::shared_ptr<RemoteClientInstruction>&
                                                        ptr_instruction) {
    Packet packet;
    socket.receive(packet, ONE_BYTE);
    char action = packet.getByte();
    switch (action) {
        case 'c':
            this->fillClientInstructionWithChat(socket, ptr_instruction);
            break;
        case 'l':
            std::cout << "hola" << std::endl;
            this->fillClientInstructionWithLoadBoard(socket, ptr_instruction);
            break;
        case 'e':
            this->fillClientInstructionWithExitMessage(socket, ptr_instruction);
            break;
    }

}


