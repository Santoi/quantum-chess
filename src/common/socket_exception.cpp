#include "socket_exception.h"
#include <string>
#include <utility>

SocketException::SocketException(std::string &&msg) noexcept: msg(
    std::move(msg)) {}

const char *SocketException::what() const noexcept {
  return msg.c_str();
}
