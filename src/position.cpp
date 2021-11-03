#include <stdexcept>
#include "position.h"

Position::Position(uint8_t x, uint8_t y): x_(0), y_(0) {
    if (x > 7 || y > 7)
        throw std::invalid_argument("posicion invalida");
    x_ = x;
    y_ = y;
}

int8_t Position::x() const {
    return x_;
}

int8_t Position::y() const {
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







