#ifndef QUANTUM_CHESS_PROJ_SOCKET_H
#define QUANTUM_CHESS_PROJ_SOCKET_H

#include <cstddef>
#include <cstdint>
#include <unistd.h>
#include <exception>
#include <memory>

#include "network.h"
#include "packet.h"

class Socket {
private:
  int fd;
  Network network;

public:
  //A new socket is created by assigning other_socket's fd to new socket's fd.
  // Other socket's fd is set to be invalid_fd.
  Socket(Socket &&other) noexcept;

  Socket &operator=(Socket &&other) noexcept;

  Socket(const Socket &other) = delete;

  Socket &operator=(const Socket &other) = delete;

  //Creates and returns a client socket using the host and service provided,
  // connecting it accordingly
  static Socket createAConnectedSocket(const char *host, const char *service);

  template<typename T, typename... Args>
  friend std::unique_ptr<T> make_unique(Args &&... args);

  //Creates a server socket using the host and service provided. A bind and a
  // listen are applied to the new socket, leaving it on a valid state for
  // accepting client sockets. The server socket is returned.
  static Socket createAListeningSocket(const char *host, const char *service);

  // Wait for a new socket to connect
  Socket accept() const;

  // Sends the contents of the packet
  size_t send(Packet &packet) const;

  // Receives size bytes from socket, storing them in the given packet
  size_t receive(Packet &packet, size_t size) const;

  // The given socket is shutdown and closed
  void shutdownAndClose();

  // Sockets resources are freed. Socket it is shutdown and closed
  ~Socket();

private:
  // A socket with an invalid fd is created
  Socket();

  // A socket is created with a valid file descriptor passed by parameter
  explicit Socket(int valid_fd);

  //Socket is created initializing the network configuration
  Socket(const char *hostname, const char *service);

  // Socket is initialized using the host and service parameters
  // It is connected to the appropriate socket
  void connect();

  // Socket is initialized and bound
  // Once bound it listens for connections
  void bindAndListen();

  const struct addrinfo *open();
};


#endif // QUANTUM_CHESS_PROJ_SOCKET_H
