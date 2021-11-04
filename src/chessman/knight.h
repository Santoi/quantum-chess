#ifndef QUANTUM_CHESS_PROJ_KNIGHT_H
#define QUANTUM_CHESS_PROJ_KNIGHT_H

#include <iostream>
#include "chessman.h"
#include "../position.h"

class Knight: public Chessman {
private:
    std::string print() const override;

public:
    Knight(const Position & position, bool white_, Board & board_);
    void calculatePosibleMoves(const Position &initial, std::vector<Position> &posible_moves) const override;

    ~Knight() override = default;

    void calculatePath(const Position &initial, const Position &final, std::vector<Position> &path) const override;
};


#endif //QUANTUM_CHESS_PROJ_KNIGHT_H
