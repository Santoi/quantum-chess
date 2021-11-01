#include <stdexcept>
#include "position.h"

Position::Position(uint8_t x, uint8_t y): x_(0), y_(0) {
    if(x > 7 || y > 7)
        throw std::invalid_argument("posicion invalida");
    x_ = x;
    y_ = y;
}

uint8_t Position::x() const {
    return x_;
}

uint8_t Position::y() const {
    return y_;
}


