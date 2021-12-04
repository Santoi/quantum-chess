#include <vector>
#include <algorithm>
#include <list>
#include "quantum_position.h"
#include "../../../common/src/chess_exception.h"
#include "chessman/chessman.h"

QuantumPosition::QuantumPosition(uint8_t x, uint8_t y, double prob_,
                                 Chessman *chessman_) : position(x, y),
                                                        prob(prob_),
                                                        chessman(chessman_) {
  if (prob > 1 || prob < 0)
    throw ChessException("invalid probability");
}

QuantumPosition::QuantumPosition(const Position &position_, double prob_,
                                 Chessman *chessman_) : position(position_),
                                                        prob(prob_),
                                                        chessman(chessman_) {
  if (prob > 1 || prob < 0)
    throw ChessException("invalid probability");
}

uint8_t QuantumPosition::x() const {
  return position.x();
}

uint8_t QuantumPosition::y() const {
  return position.y();
}

double QuantumPosition::getProb() const {
  return prob;
}

bool QuantumPosition::operator==(const QuantumPosition &other) const {
  return position == other.position
         && compareDoubleWithPrecision(prob, other.prob, PRECISION_PROB);
}

bool QuantumPosition::operator!=(const QuantumPosition &other) const {
  return !(*this == other);
}

bool QuantumPosition::operator==(const Position &other) const {
  return other == position;
}

bool QuantumPosition::operator!=(const Position &other) const {
  return !(*this == other);
}

void QuantumPosition::setProb(double prob_) {
  if (prob < 0 || prob > 1)
    throw ChessException("invalid probability");
  prob = prob_;
}

void QuantumPosition::measure() {
  if (chessman)
    chessman->measure(Position(*this));
  else
    throw std::runtime_error("trying to measure a position not assigned to"
                             "chessman");
}

bool QuantumPosition::compareDoubleWithPrecision(double a, double b,
                                                 double e) const {
  return std::abs(a - b) < e;
}

void QuantumPosition::setPosition(const Position &position_) {
  position = position_;
}

const Chessman &QuantumPosition::getChessman() {
  return *chessman;
}

bool QuantumPosition::isMyChessman(const Chessman &chessman_) const {
  return &chessman_ == chessman;
}


