#ifndef QUANTUM_CHESS_PROJ_PAWN_H
#define QUANTUM_CHESS_PROJ_PAWN_H

#include <iostream>
#include "chessman.h"
#include "../position.h"

class Pawn: public Chessman {
private:
    bool first_move;

    std::string print() const override;

public:
    Pawn(const Position & position, bool white_, Board & board_);

    void move(const Position & initial, const Position & final) override;

    void calculatePosibleMoves(const Position &initial, std::vector<Position> &posible_moves) const override;

    ~Pawn() override = default;
};


#endif //QUANTUM_CHESS_PROJ_PAWN_H
