#include <stdexcept>
#include <iostream>
#include "position.h"
#include "../../../common/src/chess_exception.h"
#include "quantum_position.h"

Position::Position() : x_(0), y_(0) {}

Position::Position(uint8_t x, uint8_t y) : x_(x), y_(y) {
  if (x > 7 || y > 7)
    throw ChessException("invalid position");
}

Position::Position(const QuantumPosition &position) :
        x_(position.x()), y_(position.y()) {}

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

bool Position::operator==(const QuantumPosition &other) const {
  return *this == Position(other.x(), other.y());
}

bool Position::operator!=(const QuantumPosition &other) const {
  return !(*this == other);
}

bool operator<(const Position &a, const Position &b) {
  return (a.x_ < b.x_) ||
         ((a.x_ == b.x_) && (a.y_ < b.y_));
}

std::string Position::print() const {
  std::string out;
  out.push_back(x_ + 'A');
  out.push_back(y_ + '1');
  return out;
}









