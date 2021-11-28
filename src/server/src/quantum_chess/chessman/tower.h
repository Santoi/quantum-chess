#ifndef QUANTUM_CHESS_PROJ_TOWER_H
#define QUANTUM_CHESS_PROJ_TOWER_H

#include <vector>
#include <string>
#include "chessman.h"
#include "../position.h"

class Tower : public Chessman {
private:
  char print() const override;

public:
  Tower(const Position &position, bool white_, Board &board_,
        EntanglementLog &entanglement_log_);

  void calculateMoves(const Position &initial,
                      std::list<Position> &posible_moves)
  const override;

  ~Tower() override = default;
};


#endif //QUANTUM_CHESS_PROJ_TOWER_H
