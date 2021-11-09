#include "common_packet.h"
#include <unistd.h>
#include <arpa/inet.h>

#include "client_protocol.h"

#define ONE_BYTE 1
#define TWO_BYTES 2

int ClientProtocol::receiveNumberOfRunningGames(Socket& socket) {
    Packet packet;
    socket.receive(packet, TWO_BYTES);
    uint16_t number_of_gamesBE;
    packet.getBytes(number_of_gamesBE);
    return (int)(ntohs(number_of_gamesBE));
}

void ClientProtocol::sendChosenGame(Socket& socket, const int& game_number) {
    Packet packet;
    uint16_t host_game_number = game_number;
    uint16_t game_numberBE = htons(host_game_number);
    packet.addBytes(game_numberBE);
    socket.send(packet);
}

void ClientProtocol::sendMessage(Socket& socket, const std::string& message) {
    Packet packet;
    packet.addByte('c');
    uint16_t host_length = message.size();
    uint16_t lengthBE = htons(host_length);
    packet.addBytes(lengthBE);
    packet.addBytes(message);
    socket.send(packet);
}

void ClientProtocol::receiveInstruction(Socket& socket, std::string& message) {
    Packet packet;
    socket.receive(packet, ONE_BYTE);
    socket.receive(packet, TWO_BYTES);
    uint16_t size_of_wordBE;
    packet.getBytes(size_of_wordBE);
    uint16_t size_of_word = ntohs(size_of_wordBE);
    socket.receive(packet, size_of_word);
    packet.getBytes(message, size_of_word);
}

