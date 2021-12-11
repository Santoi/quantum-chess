#include "position.h"
#include "../../common/chess_exception.h"
#include <iostream>
#include <cstdint>

#define BOUND 7

Position::Position() : x_(0), y_(0) {}

Position::Position(int8_t x, int8_t y) : x_(x), y_(y) {
  if (x > BOUND || y > BOUND)
    throw ChessException("Invalid position");
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
  return !(*this == other);
}

bool operator<(const Position &a, const Position &b) {
  return (a.x_ < b.x_) ||
         ((a.x_ == b.x_) && (a.y_ < b.y_));
}

std::ostream &operator<<(std::ostream &os, const Position &position) {
  os << "(" << (uint) position.x_ << ", " << (uint) position.y_ << ")";
  return os;
}

bool Position::isEven() const {
  return (x_ + y_) % 2 == 0;
}
