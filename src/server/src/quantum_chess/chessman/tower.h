#ifndef QUANTUM_CHESS_PROJ_TOWER_H
#define QUANTUM_CHESS_PROJ_TOWER_H

#include <vector>
#include <string>
#include "chessman.h"
#include "../position.h"

class Tower : public Chessman {
private:
  bool first_move;

  char charId() const override;

  friend class King;

public:
  Tower(const Position &position, bool white_, Board &board_,
        EntanglementLog &entanglement_log_);

  void calculateMoves(const Position &initial,
                      std::list<Position> &posible_moves)
  const override;

  bool move(const Position &initial, const Position &final) override;

  ~Tower() override = default;

  bool notMovedYet();

  void
  split(const Position &initial, const Position &final1,
        const Position &final2) override;
};


#endif //QUANTUM_CHESS_PROJ_TOWER_H
