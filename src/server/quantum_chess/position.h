#ifndef QUANTUM_CHESS_PROJ_POSITION_H
#define QUANTUM_CHESS_PROJ_POSITION_H

#include <cstdint>
#include <iostream>
#include <string>

class QuantumPosition;

// Represents a position in chessboard
class Position {
  uint8_t x_, y_;

public:
  Position();

  Position(uint8_t x, uint8_t y);

  Position(const Position &orig) = default;

  // Constructor from QuantumPosition object. It keeps position parameter
  // of it
  explicit Position(const QuantumPosition &position);

  Position &operator=(const Position &orig) = default;

  bool operator==(const Position &other) const;

  bool operator!=(const Position &other) const;

  // Compares with Position field of QuantumPosition
  bool operator==(const QuantumPosition &other) const;

  // Compares with Position field QuantumPosition
  bool operator!=(const QuantumPosition &other) const;

  // Returns x coordinate
  uint8_t x() const;

  // Returns y coordinate
  uint8_t y() const;

  friend bool operator<(const Position &a, const Position &b);

  std::string print() const;
};


#endif //QUANTUM_CHESS_PROJ_POSITION_H
