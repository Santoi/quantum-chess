#include "board_position.h"
#include "../../common/chess_exception.h"
#include <iostream>
#include <cstdint>

#define BOUND 8

BoardPosition::BoardPosition() : x_(0), y_(0) {}

BoardPosition::BoardPosition(int8_t x, int8_t y) : x_(x), y_(y) {
  if (x > BOUND || y > BOUND)
    throw ChessException("Invalid position");
}

int8_t BoardPosition::x() const {
  return x_;
}

int8_t BoardPosition::y() const {
  return y_;
}

bool BoardPosition::operator==(const BoardPosition &other) const {
  return x_ == other.x_ && y_ == other.y_;
}

bool BoardPosition::operator!=(const BoardPosition &other) const {
  return !(*this == other);
}

bool operator<(const BoardPosition &a, const BoardPosition &b) {
  return (a.x_ < b.x_) ||
         ((a.x_ == b.x_) && (a.y_ < b.y_));
}

std::ostream &operator<<(std::ostream &os, const BoardPosition &position) {
  os << "(" << (uint) position.x_ << ", " << (uint) position.y_ << ")";
  return os;
}

bool BoardPosition::isEven() const {
  return (x_ + y_) % 2 == 0;
}
