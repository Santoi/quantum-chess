#ifndef QUANTUM_CHESS_PROJ_BOARD_POSITION_H
#define QUANTUM_CHESS_PROJ_BOARD_POSITION_H

#include <iostream>
#include <cstdint>

// Represents a tile position inside the board
// Bottom right is (0, 0) and top left is (BOUND, BOUND)
// -1 position is used to draw the board's coordinates
class BoardPosition {
private:
  int8_t x_ = 0;
  int8_t y_ = 0;

public:
  BoardPosition();

  BoardPosition(int8_t x, int8_t y);

  ~BoardPosition() = default;

  BoardPosition(const BoardPosition &orig) = default;

  BoardPosition &operator=(const BoardPosition &orig) = default;

  bool operator==(const BoardPosition &other) const;

  bool operator!=(const BoardPosition &other) const;

  friend bool operator<(const BoardPosition &a, const BoardPosition &b);

  // Return x coordinate.
  int8_t x() const;

  // Return y coordinate.
  int8_t y() const;

  friend std::ostream &operator<<(std::ostream &os,
                                  const BoardPosition &position);

  // Returns true if the coordinate sum is even
  // Used to set the board's color
  bool isEven() const;
};


#endif //QUANTUM_CHESS_PROJ_BOARD_POSITION_H
