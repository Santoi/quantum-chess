#include <stdexcept>
#include <iostream>
#include "position.h"
#include "chess_exception.h"

Position::Position(): x_(0), y_(0) {}

Position::Position(uint8_t x, uint8_t y): x_(0), y_(0) {
    if (x > 7 || y > 7)
        throw ChessException("posicion invalida");
    x_ = x;
    y_ = y;
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
    return x_ != other.x_ || y_ != other.y_;
}

Position & Position::operator=(const Position & orig) {
    x_ = orig.x_;
    y_ = orig.y_;
    return *this;
}

bool operator<(const Position &a, const Position &b) {
    return (a.x_ < b.x_) ||
           ((a.x_ == b.x_) && (a.y_ < b.y_));
}

std::ostream & operator<<(std::ostream & os, const Position & position){
    os << "(" << (uint) position.x_ << ", " << (uint) position.y_ << ")";
    return os;
}







