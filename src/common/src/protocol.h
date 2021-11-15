#ifndef QUANTUM_CHESS_PROJ_PROTOCOL_H
#define QUANTUM_CHESS_PROJ_PROTOCOL_H

#include "packet.h"
#include "socket.h"
#include <arpa/inet.h>

class Protocol {
protected:
    //Adds 1. the given string length (in Big Endian) and 2. the string to the given packet.
    void addStringAndItsLengthToPacket(Packet& packet, const std::string& string);

    //Transforms the given number in host order to Big Endian and then adds it to the given packet.
    void changeNumberToBigEndianAndAddToPacket(Packet& packet, const uint16_t& number);

    //Gets the Big Endian number from socket, transforms it to host order and returns it.
    uint16_t getNumberFromSocket(Socket& socket);

    //Reads the next message from socket, saving it in the message string.
    void getMessageFromSocket(Socket& socket, std::string& message);

private:
    //Gets from socket the string of size size_of_word, and saves it in the message string.
    void getMessageOfSizeFomSocket(Socket& socket, std::string& message, const uint16_t& size_of_word);
};


#endif //QUANTUM_CHESS_PROJ_PROTOCOL_H
