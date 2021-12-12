#include <vector>
#include <string>
#include "chessman.h"
#include "tower.h"

Tower::Tower(const Position &position, bool white_, Board &board_,
             EntanglementLog &entanglement_log_) :
        Chessman(position, white_, board_, entanglement_log_),
        first_move(true) {}

void Tower::calculateMoves(const Position &initial,
                           std::list<Position> &possible_moves)
const {
  possible_moves = std::list<Position>();
  Position position;
  // Column is checked.
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
}

char Tower::charId() const {
  return 'T';
}

bool Tower::move(const Position &initial, const Position &final) {
  bool capture = Chessman::move(initial, final);
  first_move = false;
  return capture;
}

bool Tower::hasNotMovedYet() {
  return first_move;
}

void Tower::split(const Position &initial, const Position &final1,
                  const Position &final2) {
  Chessman::split(initial, final1, final2);
  first_move = false;
}
