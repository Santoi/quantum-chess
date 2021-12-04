#ifndef QUANTUM_CHESS_PROJ_QUANTUM_POSITION_H
#define QUANTUM_CHESS_PROJ_QUANTUM_POSITION_H

#include <list>
#include "position.h"

#define PRECISION_PROB 1.5258e-5

class Position;

class Chessman;

// Represents a Quantum Position. It has as attributes its position, its
// probability and a reference to its Chessman.
class QuantumPosition {
  Position position;
  double prob;
  Chessman *chessman;

// Compare a double with precision, used to compare probabilities.
  bool compareDoubleWithPrecision(double a, double b, double e) const;

public:
  // Constructor from Position object.
  QuantumPosition(const Position &position_, double prob_,
                  Chessman *chessman_ = nullptr);

  // Constructor from x and y coordinates.
  QuantumPosition(uint8_t x, uint8_t y, double prob_,
                  Chessman *chessman_ = nullptr);

  bool operator==(const QuantumPosition &other) const;

  bool operator!=(const QuantumPosition &other) const;

  // Compares with Position object.
  bool operator==(const Position &other) const;

  // Compares with Position object.
  bool operator!=(const Position &other) const;

  // Returns x coordinate.
  uint8_t x() const;

  // Returns y coordinate.
  uint8_t y() const;

  // Returns probability.
  double getProb() const;

  // Sets probability.
  void setProb(double prob_);

  // Sets position.
  void setPosition(const Position &position_);

  // Measures Quantum position's chessman.
  void measure();

  // Returns true if a chessman is equal to Quantum Position one.
  bool isMyChessman(const Chessman &chessman_) const;

  // Returns reference to its chessman.
  const Chessman &getChessman();
};


#endif //QUANTUM_CHESS_PROJ_QUANTUM_POSITION_H
