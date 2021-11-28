#ifndef QUANTUM_CHESS_PROJ_KNIGHT_H
#define QUANTUM_CHESS_PROJ_KNIGHT_H

#include <vector>
#include <string>
#include "chessman.h"
#include "../position.h"

class Knight : public Chessman {
private:
  char print() const override;

public:
  Knight(const Position &position, bool white_, Board &board_,
         EntanglementLog &entanglement_log_);

  void calculateMoves(const Position &initial,
                      std::list<Position> &posible_moves)
  const override;

  void calculatePath(const Position &initial, const Position &final,
                     std::vector<Position> &path) const override;

  ~Knight() override = default;
};


#endif //QUANTUM_CHESS_PROJ_KNIGHT_H
