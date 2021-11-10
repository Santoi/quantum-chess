#include "server_protocol.h"
#include "common_packet.h"
#include "instructions.h"
#include <unistd.h>
#include <arpa/inet.h>

#define ONE_BYTE 1
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

void ServerProtocol::getNickName(Socket& socket, std::string& nick_name) {
    Packet packet;
    socket.receive(packet, TWO_BYTES);
    uint16_t size_of_wordBE;
    packet.getBytes(size_of_wordBE);
    uint16_t size_of_word = ntohs(size_of_wordBE);
    socket.receive(packet, size_of_word);
    packet.getBytes(nick_name, size_of_word);
}


void ServerProtocol::fillPacketWithChatInstructions(Socket& socket, std::shared_ptr<Instruction>&
                                                                    instruct_ptr) {
    Packet packet;
    socket.receive(packet, TWO_BYTES);
    uint16_t size_of_wordBE;
    packet.getBytes(size_of_wordBE);
    uint16_t size_of_word = ntohs(size_of_wordBE);
    socket.receive(packet, size_of_word);
    std::string message;
    packet.getBytes(message, size_of_word);
    instruct_ptr = std::make_shared<ChatInstruction>(std::move(message));
}

void ServerProtocol::fillPacketWithMovementInstructions(Socket& socket, std::shared_ptr<Instruction>&
                                                                    instruct_ptr) {

}

void ServerProtocol::fillPacketWithInstructions(Socket& socket, std::shared_ptr<Instruction>&
                                                                    instruct_ptr) {
    Packet packet;
    socket.receive(packet, ONE_BYTE);
    char action = packet.getByte();
    if (action == 'c')
        fillPacketWithChatInstructions(socket, instruct_ptr);
    else
        fillPacketWithMovementInstructions(socket, instruct_ptr);
}

void ServerProtocol::sendPacketWithUpdates(Socket& socket, std::shared_ptr<Instruction>& instruct_ptr) {
    Packet packet;
    instruct_ptr->fillPacketWithInstructionsToSend(packet);
    socket.send(packet);
}

