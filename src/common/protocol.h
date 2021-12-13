#ifndef QUANTUM_CHESS_PROJ_PROTOCOL_H
#define QUANTUM_CHESS_PROJ_PROTOCOL_H

#include "packet.h"
#include "socket.h"
#include <arpa/inet.h>
#include <string>

class Protocol {
protected:
  // Adds the given string, and it's length in Big Endian, to the given packet
  void addStringAndItsLengthToPacket(Packet &packet, const std::string &string);

  void
  changeNumberToBigEndianAndAddToPacket(Packet &packet, const uint16_t &number);

  uint16_t getNumber16FromSocket(Socket &socket);

  // Reads the next message from socket, saving it in the message string.
  void getMessageFromSocket(Socket &socket, std::string &message);

  char getCharFromSocket(Socket &socket);

  uint8_t getNumber8FromSocket(Socket &socket);

  void addNumber8ToPacket(Packet &packet, const uint8_t &number);

private:
  void getMessageOfSizeFromSocket(Socket &socket, std::string &message,
                                  const uint16_t &size_of_word);
};


#endif //QUANTUM_CHESS_PROJ_PROTOCOL_H
