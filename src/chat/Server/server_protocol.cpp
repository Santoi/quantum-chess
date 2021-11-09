#include "server_protocol.h"
#include "common_packet.h"
#include <unistd.h>
#include <arpa/inet.h>

#define TWO_BYTES 2

void ServerProtocol::sendNumberOfGamesRunning(Socket& socket, const int& max_games) {
    Packet packet;
    uint16_t host_max_games = max_games;
    uint16_t max_gamesBE = htons(host_max_games);
    packet.addBytes(max_gamesBE);
    socket.send(packet);
}

int ServerProtocol::receiveNumberOfChosenGame(Socket& socket) {
    Packet packet;
    socket.receive(packet, TWO_BYTES);
    uint16_t game_numberBE;
    packet.getBytes(game_numberBE);
    return (int)(ntohs(game_numberBE));
}

