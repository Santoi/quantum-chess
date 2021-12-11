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

  // Performs a long castling, moving king and left tower.
  void longCastling(
          const std::_List_iterator<QuantumPosition> &position_to_castle);

  // Performs a short castling, moving king and right tower.
  void shortCastling(
          const std::_List_iterator<QuantumPosition> &position_to_castle);

  // Returns true if a long castling can be done.
  bool checkLongCastling() const;

  // Returns true if a short castling can be done.
  bool checkShortCastling() const;

  // Splits doing a castling.
  void splitWithCastling(const Position &final1, const Position &final2);

public:
  King(const Position &position, bool white_, Board &board_,
       EntanglementLog &entanglement_log_);

  void calculateMoves(const Position &initial,
                      std::list<Position> &posible_moves) const override;

  void calculatePossibleSplits(const Position &initial,
                               std::list<Position> &possible_moves) override;

  bool move(const Position &initial, const Position &final) override;

  void
  split(const Position &initial, const Position &final1,
        const Position &final2) override;

  ~King() override = default;


};


#endif //QUANTUM_CHESS_PROJ_KING_H
