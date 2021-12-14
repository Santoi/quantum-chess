#include "network.h"
#include "network_address_info_exception.h"
#include <netdb.h>
#include <cstring>
#include <string>

Network::Network() = default;

Network::Network(const char *hostname, const char *service) {
  struct addrinfo hints{};
  std::memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET; // IPV4
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP; // TPC protocol
  hints.ai_flags = hostname == nullptr ? AI_PASSIVE : 0; // Socket may bind
  if (getaddrinfo(hostname, service, &hints, &first))
    throw NetworkAddressInfoException("failed setting up network");
  address = next = first;
}

Network::Network(Network &&other) noexcept {
  first = other.first;
  next = other.next;
  address = other.address;
  other.first = other.next = other.address = nullptr;
}

Network &Network::operator=(Network &&other) noexcept {
  first = other.first;
  next = other.next;
  address = other.address;
  other.first = other.next = other.address = nullptr;
  return *this;
}

const struct addrinfo *Network::findAddress() {
  address = next;
  if (next != nullptr)
    next = next->ai_next;
  return address;
}

Network::~Network() {
  if (first != nullptr)
    freeaddrinfo(first);
}
