#ifndef QUANTUM_CHESS_PROJ_PAWN_H
#define QUANTUM_CHESS_PROJ_PAWN_H

#include <vector>
#include <string>
#include <list>
#include "chessman.h"
#include "../position.h"

class Pawn : public Chessman {
private:
  bool first_move;

  char charId() const override;

public:
  Pawn(const Position &position, bool white_, Board &board_,
       EntanglementLog &entanglement_log_);

  bool move(const Position &initial, const Position &final) override;

  void calculateMoves(const Position &initial,
                      std::list<Position> &possible_moves)
  const override;

  ~Pawn() override = default;

  void calculatePossibleSplits(const Position &initial,
                               std::list<Position> &possible_moves) override;

  void calculatePossibleMerges(const Position &initial,
                               std::list<Position> &possible_moves) override;

  MoveValidationStatus
  checkIsAValidMove(const Position &initial, const Position &final) override;

  MoveValidationStatus
  checkIsAValidSplit(const Position &initial, const Position &final) override;

  MoveValidationStatus
  checkIsAValidMerge(const Position &initial1,
                     const Position &final) override;
};


#endif //QUANTUM_CHESS_PROJ_PAWN_H
