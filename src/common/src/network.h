#ifndef QUANTUM_CHESS_PROJ_NETWORK_H
#define QUANTUM_CHESS_PROJ_NETWORK_H

#include <string>
#include <netdb.h>

class Network {
private:
  struct addrinfo *first{};
  struct addrinfo *address{};
  struct addrinfo *next{};

public:
  Network();

  Network(Network &&other) noexcept;

  Network(const char *hostname, const char *service);

  ~Network();

  Network &operator=(Network &&other) noexcept;

  // Returns a pointer to the next available Address
  // May return nullptr
  const struct addrinfo *findAddress();
};

#endif // QUANTUM_CHESS_PROJ_NETWORK_H
