#include <stdexcept>
#include <iostream>
#include "position.h"
#include "../../server/src/quantum_chess/chess_exception.h"
#include "../../server/src/quantum_chess/quantum_position.h"

Position::Position(): x_(0), y_(0) {}

Position::Position(uint8_t x, uint8_t y): x_(x), y_(y) {
    if (x > 7 || y > 7)
        throw ChessException("posicion invalida");
}

uint8_t Position::x() const {
    return x_;
}

uint8_t Position::y() const {
    return y_;
}

bool Position::operator==(const Position &other) const {
    return x_ == other.x_ && y_ == other.y_;
}

bool Position::operator!=(const Position &other) const {
    return !(*this == other);
}

bool operator<(const Position &a, const Position &b) {
    return (a.x_ < b.x_) ||
           ((a.x_ == b.x_) && (a.y_ < b.y_));
}

std::ostream & operator<<(std::ostream & os, const Position & position){
    os << "(" << (uint) position.x_ << ", " << (uint) position.y_ << ")";
    return os;
}









