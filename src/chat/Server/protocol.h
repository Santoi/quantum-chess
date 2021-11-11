#ifndef QUANTUM_CHESS_PROJ_PROTOCOL_H
#define QUANTUM_CHESS_PROJ_PROTOCOL_H

#include "common_packet.h"
#include "common_socket.h"
#include <arpa/inet.h>

class Protocol {

protected:
    void addStringAndItsLengthToPacket(Packet& packet, const std::string& string);
    void changeNumberToBigEndianAndAddToPacket(Packet& packet, const uint16_t& number);
    uint16_t getNumberFromSocket(Socket& socket);
    void getMessageFromSocket(Socket& socket, std::string& message);
private:
    void getMessageOfSizeFomSocket(Socket& socket, std::string& message, const uint16_t& size_of_word);
};


#endif //QUANTUM_CHESS_PROJ_PROTOCOL_H
