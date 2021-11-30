#ifndef QUANTUM_CHESS_PROJ_KING_H
#define QUANTUM_CHESS_PROJ_KING_H

#include <vector>
#include <string>
#include "chessman.h"
#include "../position.h"

class King : public Chessman {
private:
  bool first_move;
  uint8_t first_line;

  char charId() const override;

  void longCastling(
          const std::_List_iterator<QuantumPosition> &position_to_castle);

  void shortCastling(
          const std::_List_iterator<QuantumPosition> &position_to_castle);

  bool checkLongCastling() const;

  bool checkShortCastling() const;

public:
  King(const Position &position, bool white_, Board &board_,
       EntanglementLog &entanglement_log_);

  void calculateMoves(const Position &initial,
                      std::list<Position> &posible_moves)
  const override;

  bool move(const Position &initial, const Position &final) override;

  ~King() override = default;

  void
  split(const Position &initial, const Position &final1,
        const Position &final2) override;

  void splitWithCastling(const Position &final1, const Position &final2);

  void calculatePossibleSplits(const Position &initial,
                               std::list<Position> &posible_moves) override;
};


#endif //QUANTUM_CHESS_PROJ_KING_H
