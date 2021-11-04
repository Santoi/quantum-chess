#ifndef QUANTUM_CHESS_PROJ_QUEEN_H
#define QUANTUM_CHESS_PROJ_QUEEN_H

#include <iostream>
#include "chessman.h"
#include "../position.h"

class Queen: public Chessman {
private:
    std::string print() const override;
public:
    Queen(const Position & position, bool white_, Board & board_);
    void calculatePosibleMoves(const Position &initial, std::vector<Position> &posible_moves) const override;

    ~Queen() override = default;
};


#endif //QUANTUM_CHESS_PROJ_QUEEN_H
