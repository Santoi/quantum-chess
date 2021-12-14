#include "protocol.h"
#include "socket_closed.h"
#include <string>

void Protocol::addStringAndItsLengthToPacket(Packet &packet,
                                             const std::string &string) {
  uint16_t host_length = string.size();
  this->changeNumberToBigEndianAndAddToPacket(packet, host_length);
  packet.addBytes(string);
}

void Protocol::changeNumberToBigEndianAndAddToPacket(Packet &packet,
                                                     const uint16_t &number) {
  uint16_t numberBE = htons(number);
  packet.addBytes(numberBE);
}

void Protocol::addNumber8ToPacket(Packet &packet, const uint8_t &number) {
  packet.addBytes(number);
}

uint16_t Protocol::getNumber16FromSocket(const Socket &socket) {
  Packet packet;
  socket.receive(packet, 2);
  if (packet.size() != 2)
    throw SocketClosed();
  uint16_t number;
  packet.getBytes(number);
  return ntohs(number);
}

char Protocol::getCharFromSocket(const Socket &socket) {
  Packet packet;
  socket.receive(packet, 1);
  if (packet.size() != 1)
    throw SocketClosed();
  char character = packet.getByte();
  return character;
}

uint8_t Protocol::getNumber8FromSocket(Socket &socket) {
  Packet packet;
  socket.receive(packet, 1);
  if (packet.size() != 1)
    throw SocketClosed();
  char character = packet.getByte();
  auto *number = (uint8_t *) &character;
  return *number;
}

void
Protocol::getMessageOfSizeFromSocket(const Socket &socket, std::string &message,
                                     const uint16_t &size_of_word) {
  Packet packet;
  socket.receive(packet, size_of_word);
  if (packet.size() != size_of_word)
    throw SocketClosed();
  packet.getBytes(message, size_of_word);
}

void Protocol::getMessageFromSocket(Socket &socket, std::string &message) {
  uint16_t size_of_nick_name = this->getNumber16FromSocket(socket);
  ((Protocol) (*this)).getMessageOfSizeFromSocket(socket, message,
                                                  size_of_nick_name);
}

