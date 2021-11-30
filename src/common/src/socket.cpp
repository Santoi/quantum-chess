#include "socket.h"
#include "socket_closed.h"
#include "socket_exception.h"
#include "unique_ptr.h"
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstdint>
#include <cstdio>
#include <iostream>

#define ERROR -1
#define MAX_QUEUE 8
#define INVALID_FILE_DESCRIPTOR -1

Socket::Socket() : fd(INVALID_FILE_DESCRIPTOR) {
}

Socket::Socket(int fd_valido) : fd(fd_valido) {
}

Socket::Socket(const char *hostname, const char *service) : fd(-1),
                                                            network(hostname,
                                                                    service) {}

Socket::Socket(Socket &&other) noexcept {
  fd = other.fd;
  other.fd = INVALID_FILE_DESCRIPTOR;
}

Socket Socket::createAConnectedSocket(const char *host, const char *service) {
  Socket skt(host, service);
  skt.connect();
  return skt;
}

void Socket::createAConnectedSocket(std::unique_ptr<Socket>& socket_ptr, const char* host, const char* service) {
    socket_ptr = make_unique<Socket>(host, service);
    socket_ptr->connect();
}

Socket Socket::createAListeningSocket(const char *host, const char *service) {
  Socket skt(host, service);
  skt.bindAndListen();
  return skt;
}

void Socket::connect() {
  bool connected = false;
  while (!connected) {
    shutdownAndClose();
    const addrinfo *address = open();
    connected = !::connect(fd, address->ai_addr, address->ai_addrlen);
  }
}

void Socket::bindAndListen() {
  bool bound = false;
  while (!bound) {
    shutdownAndClose();
    const struct addrinfo *address = open();
    int aux = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &aux, sizeof(aux)) < 0)
      throw SocketException("binding failed");
    bound = !::bind(fd, address->ai_addr, address->ai_addrlen);
  }
  if (::listen(fd, MAX_QUEUE))
    throw SocketException("Error trying to listen for connections");
}

Socket Socket::accept() const {
  int new_fd = ::accept(fd, nullptr, nullptr);
  if (new_fd == INVALID_FILE_DESCRIPTOR) {
    if (errno == EBADF || errno == EINVAL)
      throw SocketClosed();
    throw SocketException("can't accept socket connection");
  }
  Socket socket_cliente(new_fd);
  return socket_cliente;
}

size_t Socket::send(Packet &packet) const {
  if (fd == INVALID_FILE_DESCRIPTOR)
    throw SocketException("uninitialized socket");
  packet.resetSent();
  // Mientras que quede algo pendiente de enviar se itera.
  while (packet.pendingToSentSize() > 0) {
    // Se envian los datos pendientes.
    ssize_t bytes_sent = ::send(fd, packet.getPendingToSent(),
                                packet.pendingToSentSize(), MSG_NOSIGNAL);
    // Si no se envio nada se lanza excepcion de socket cerrado.
    if (bytes_sent == 0)
      throw SocketClosed();
    if (bytes_sent == -1) {
      if (errno == EPIPE)
        throw SocketClosed();
      throw std::runtime_error("failed to send data");
    }
    // Se contabiliza la cantidad de bytes enviados.
    packet.addSentAmount(bytes_sent);
  }
  // Se devuelve la cantidad de bytes enviados.
  return packet.sent();
}

size_t Socket::receive(Packet &packet, size_t size) const {
  if (fd == INVALID_FILE_DESCRIPTOR)
    throw SocketException("uninitialized socket");
  // Se crea un buffer para recibir.
  std::vector<char> buffer(size, 0);
  packet.reset();
  while (packet.size() < size) {
    // Se recibe el tamanio del buffer.
    ssize_t bytes_recv = recv(fd, buffer.data(), size - packet.size(), 0);
    // Si no se recibio nada, socket cerrado. Sino error.
    if (bytes_recv == 0) {
      throw SocketClosed();
    }
    if (bytes_recv == -1) {
      if (errno == EBADF) {
        throw SocketClosed();
      }
      throw std::runtime_error("failed to receive data");
    }
    // Se agregan los bytes recibidos al paquete.
    packet.addBytes(buffer.data(), bytes_recv);
  }
  // Se devuelven los bytes recibidos.
  return packet.size();
}

void Socket::shutdownAndClose() {
  if (fd != INVALID_FILE_DESCRIPTOR) {
    ::shutdown(fd, SHUT_RDWR);
    int aux = ::close(fd);
    fd = INVALID_FILE_DESCRIPTOR;
    if (aux == ERROR)
      throw SocketException("couldn't close socket");
  }
}

Socket::~Socket() {
  shutdownAndClose();
}

const struct addrinfo *Socket::open() {
  const struct addrinfo *address;
  do {
    address = network.findAddress();
    if (address == nullptr)
      throw SocketException("socket couldn't open");
    fd = ::socket(address->ai_family, address->ai_socktype,
                  address->ai_protocol);
  } while (fd == INVALID_FILE_DESCRIPTOR);
  return address;
}
