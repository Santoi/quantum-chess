#ifndef QUANTUM_CHESS_PROJ_SOCKET_EXCEPTION_H
#define QUANTUM_CHESS_PROJ_SOCKET_EXCEPTION_H

#include <exception>
#include <string>

class SocketException : public std::exception {
private:
  std::string msg;

public:
  explicit SocketException(std::string msg) noexcept;

/*
  SocketException(const SocketException &other) noexcept = default;
*/
  ~SocketException() noexcept override = default;

  const char *what() const noexcept override;
};


#endif // QUANTUM_CHESS_PROJ_SOCKET_EXCEPTION_H
