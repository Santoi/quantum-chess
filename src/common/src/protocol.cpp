#include "protocol.h"

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

uint16_t Protocol::getNumber16FromSocket(Socket &socket) {
  Packet packet;
  socket.receive(packet, 2);
  uint16_t number;
  packet.getBytes(number);
  return ntohs(number);
}

char Protocol::getCharFromSocket(Socket &socket) {
  Packet packet;
  socket.receive(packet, 1);
  char character = packet.getByte();
  return character;
}

uint8_t Protocol::getNumber8FromSocket(Socket &socket) {
  Packet packet;
  socket.receive(packet, 1);
  char character = packet.getByte();
  auto *number = (uint8_t *) &character;
  return *number;
}

void Protocol::getMessageOfSizeFromSocket(Socket &socket, std::string &message,
                                          const uint16_t &size_of_word) {
  Packet packet;
  socket.receive(packet, size_of_word);
  packet.getBytes(message, size_of_word);
}

void Protocol::getMessageFromSocket(Socket &socket, std::string &message) {
  uint16_t size_of_nick_name = this->getNumber16FromSocket(socket);
  ((Protocol) (*this)).getMessageOfSizeFromSocket(socket, message,
                                                  size_of_nick_name);
}

