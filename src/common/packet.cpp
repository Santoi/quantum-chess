#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <netinet/in.h>
#include "packet.h"

Packet::Packet() : array(PREDEFINED_SIZE_BLOCK), sent_(0), read_(0), size_(0) {}

void Packet::addBytes(const char *bytes, const uint32_t &size) {
  expandUntilMatchSize(size);
  for (size_t i = 0; i < size; i++, size_++) {
    array[size_] = bytes[i];
  }
}

void Packet::addBytes(const std::string &bytes) {
  expandUntilMatchSize(bytes.size());
  for (size_t i = 0; i < bytes.size(); i++, size_++)
    array[size_] = bytes[i];
}

void Packet::addBytes(const uint16_t &bytes) {
  expandUntilMatchSize(2);
  char *bytes_ = (char *) &bytes;
  addBytes(bytes_, 2);
}

void Packet::addBytes(const uint8_t &bytes) {
  expandUntilMatchSize(1);
  char *bytes_ = (char *) &bytes;
  addBytes(bytes_, 1);
}

void Packet::addByte(char byte) {
  expandUntilMatchSize(1);
  array[size_++] = byte;
}

void Packet::getBytes(std::string &out, const uint32_t &size) {
  if ((size_ - read_) < size)
    throw std::invalid_argument("se piden mas bytes que los existentes");
  out = std::string(array.begin() + read_, array.begin() + read_ + size);
}

void Packet::getBytes(uint16_t &out) {
  if ((size_ - read_) < 2)
    throw std::invalid_argument("se piden mas bytes que los existentes");
  out = *(uint16_t *) (array.data() + read_);
  read_ += 2;
}

void Packet::addSentAmount(const size_t &sent) {
  sent_ += sent;
}

uint32_t Packet::pendingToSentSize() const {
  return size_ - sent_;
}

uint32_t Packet::sent() const {
  return sent_;
}

const char *Packet::getPendingToSent() const {
  return array.data() + sent_;
}

uint32_t Packet::size() const {
  return size_;
}

char Packet::getByte() {
  return array[read_++];
}

void Packet::reset() {
  array = std::vector<char>(PREDEFINED_SIZE_BLOCK);
  sent_ = 0;
  size_ = 0;
  read_ = 0;
}

void Packet::expandUntilMatchSize(const uint32_t &size) {
  while (array.size() < size_ + size)
    expand();
}

void Packet::expand() {
  array.resize(array.size() * 1.5);
}

void Packet::resetSent() {
  sent_ = 0;
}











