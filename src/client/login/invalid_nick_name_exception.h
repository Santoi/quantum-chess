#ifndef QUANTUM_CHESS_SRC_INVALID_NICK_NAME_EXCEPTION_H
#define QUANTUM_CHESS_SRC_INVALID_NICK_NAME_EXCEPTION_H

#include <exception>

#define MIN_NICK_NAME_LENGTH 1
#define MAX_NICK_NAME_LENGTH 16

class InvalidNickNameException : public std::exception {
public:
    InvalidNickNameException() = default;

    const char *what() const noexcept override {
        return "Invalid nickname: length has to be greater "
                "than 0 and smaller than 16.";
    }

    ~InvalidNickNameException() noexcept override = default;
};
#endif //QUANTUM_CHESS_SRC_INVALID_NICK_NAME_EXCEPTION_H
