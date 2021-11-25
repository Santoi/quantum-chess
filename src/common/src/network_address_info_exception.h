#ifndef QUANTUM_CHESS_PROJ_NETWORK_ADDRESS_INFO_EXCEPTION_H
#define QUANTUM_CHESS_PROJ_NETWORK_ADDRESS_INFO_EXCEPTION_H

#include <exception>
#include <string>

class NetworkAddressInfoException : public std::exception {
private:
  std::string msg;

public:
  explicit NetworkAddressInfoException(std::string msg);

  NetworkAddressInfoException(
      const NetworkAddressInfoException &other) noexcept = default;

  ~NetworkAddressInfoException() noexcept override = default;

  const char *what() const noexcept override;
};

#endif // QUANTUM_CHESS_PROJ_NETWORK_ADDRESS_INFO_EXCEPTION_H
