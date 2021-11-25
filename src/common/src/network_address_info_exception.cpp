#include "network_address_info_exception.h"
#include <string>
#include <utility>

NetworkAddressInfoException::NetworkAddressInfoException(std::string msg) : msg(
    std::move(msg)) {}

const char *NetworkAddressInfoException::what() const noexcept {
  return msg.c_str();
}
