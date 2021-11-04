#ifndef QUANTUM_CHESS_PROJ_BISHOP_H
#define QUANTUM_CHESS_PROJ_BISHOP_H

#include "chessman.h"
#include "../position.h"

class Bishop: public Chessman {
public:
    Bishop(const Position & position, bool white_, Board & board_);
    void calculatePosibleMoves(const Position &initial, std::vector<Position> &posible_moves) const override;
};


#endif //QUANTUM_CHESS_PROJ_BISHOP_H
