#ifndef QUANTUM_CHESS_PROJ_UNAVAILABLE_ROLE_EXCEPTION_H
#define QUANTUM_CHESS_PROJ_UNAVAILABLE_ROLE_EXCEPTION_H

#include <exception>
#include <string>

class UnavailableRoleException: public std::exception {
private:
    std::string msg;

public:
    UnavailableRoleException() = delete;

    explicit UnavailableRoleException(std::string msg) noexcept
            :msg(msg) {
    }

    const char *what() const noexcept {
        return msg.c_str();
    }

    ~UnavailableRoleException() noexcept override = default;
};


#endif //QUANTUM_CHESS_PROJ_UNAVAILABLE_ROLE_EXCEPTION_H
