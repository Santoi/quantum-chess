#include "client_protocol.h"
#include "common_packet.h"

void ClientProtocol::sendMessage(Socket& socket, const std::string& message) {
    Packet packet;
    packet.addBytes(message);
    socket.send(packet);
}


