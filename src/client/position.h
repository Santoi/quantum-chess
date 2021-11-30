#ifndef QUANTUM_CHESS_PROJ_POSITION_H
#define QUANTUM_CHESS_PROJ_POSITION_H

#include <iostream>
#include <cstdint>

// Represents a tile position inside the board
// Bottom right is (0, 0) and top left is (BOUND, BOUND)
class Position {
private:
  int8_t x_ = 0;
  int8_t y_ = 0;

public:
  Position();

  Position(int8_t x, int8_t y);

  ~Position() = default;

  Position(const Position &orig) = default;

  Position &operator=(const Position &orig) = default;

  bool operator==(const Position &other) const;

  bool operator!=(const Position &other) const;

  friend bool operator<(const Position &a, const Position &b);

  // Return x coordinate.
  int8_t x() const;

  // Return y coordinate.
  int8_t y() const;

  friend std::ostream &operator<<(std::ostream &os,
                                  const Position &position);

  bool isEven() const;
};


#endif //QUANTUM_CHESS_PROJ_POSITION_H
