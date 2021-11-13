#ifndef QUANTUM_CHESS_PROJ_POSITION_H
#define QUANTUM_CHESS_PROJ_POSITION_H

#include <cstdint>

class Position {
private:
  uint8_t x_ = 0;
  uint8_t y_ = 0;

public:
  Position();
  Position(uint8_t x, uint8_t y);
  ~Position() = default;

  Position(const Position &orig) = default;

  Position& operator=(const Position &orig) = default;

  bool operator==(const Position &other) const;

  bool operator!=(const Position &other) const;

  friend bool operator<(const Position &a, const Position &b);

  // Return x coordinate.
  uint8_t x() const;

  // Return y coordinate.
  uint8_t y() const;

  bool isEven() const;
};


#endif //QUANTUM_CHESS_PROJ_POSITION_H
