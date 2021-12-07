#ifndef QUANTUM_CHESS_PROJ_UNAVAILABLE_ROLE_EXCEPTION_H
#define QUANTUM_CHESS_PROJ_UNAVAILABLE_ROLE_EXCEPTION_H

#include <exception>
#include <string>
#include <utility>

class UnavailableRoleException : public std::exception {
public:
  UnavailableRoleException() = default;

  const char *what() const noexcept override {
    return "Selected role isn available";
  }

  ~UnavailableRoleException() noexcept override = default;
};


#endif //QUANTUM_CHESS_PROJ_UNAVAILABLE_ROLE_EXCEPTION_H
