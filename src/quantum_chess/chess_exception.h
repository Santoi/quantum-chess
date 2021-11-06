#ifndef QUANTUM_CHESS_PROJ_CHESS_EXCEPTION_H
#define QUANTUM_CHESS_PROJ_CHESS_EXCEPTION_H

#include <exception>
#include <utility>
#include <string>


class ChessException: public std::exception {
    const std::string text;

public:
    explicit ChessException(std::string text_): text(std::move(text_)) {}

    const char * what() const noexcept override {
        return text.c_str();
    }
};

#endif //QUANTUM_CHESS_PROJ_CHESS_EXCEPTION_H
