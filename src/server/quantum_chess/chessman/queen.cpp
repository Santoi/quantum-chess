#include <vector>
#include <string>
#include <algorithm>
#include "queen.h"

Queen::Queen(const Position &position, bool white_, Board &board_,
             EntanglementLog &entanglement_log_) :
        Chessman(position, white_, board_, entanglement_log_) {}

void Queen::calculateMoves(const Position &initial,
                           std::list<Position> &possible_moves)
const {
  possible_moves = std::list<Position>();
  Position position;

  // Column is checked
  for (uint8_t i = 0; i < 8; i++) {
    position = Position(initial.x(), i);
    if (position != initial)
      possible_moves.push_back(position);
  }

  // File is checked.
  for (uint8_t i = 0; i < 8; i++) {
    position = Position(i, initial.y());
    if (position != initial)
      possible_moves.push_back(position);
  }

  // Right diagonal.
  int8_t min = std::min(initial.x(), initial.y());
  for (int8_t i = initial.x() - min, j = initial.y() - min;
       i < 8 && j < 8; i++, j++) {
    position = Position(i, j);
    if (position != initial)
      possible_moves.push_back(position);
  }

  // Left diagonal.
  min = std::min(7 - initial.x(), (int) initial.y());
  for (int8_t i = initial.x() + min, j = initial.y() - min;
       i >= 0 && j < 8; i--, j++) {
    position = Position(i, j);
    if (position != initial)
      possible_moves.push_back(position);
  }
}

char Queen::charId() const {
  return 'Q';
}



