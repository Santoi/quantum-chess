#include "common_packet.h"
#include <unistd.h>
#include <arpa/inet.h>

#include "client_protocol.h"


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
    packet.addBytes(message);
    socket.send(packet);
}


