#ifndef QUANTUM_CHESS_PROJ_BISHOP_H
#define QUANTUM_CHESS_PROJ_BISHOP_H

#include <vector>
#include <string>
#include <list>
#include "chessman.h"
#include "../position.h"

class Bishop : public Chessman {
private:
  char charId() const override;

public:
  Bishop(const Position &position, bool white_, Board &board_,
         EntanglementLog &entanglement_log_);

  void calculateMoves(const Position &initial,
                      std::list<Position> &posible_moves) const override;

  ~Bishop() override = default;
};


#endif //QUANTUM_CHESS_PROJ_BISHOP_H
