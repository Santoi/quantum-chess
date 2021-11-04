#ifndef QUANTUM_CHESS_PROJ_BISHOP_H
#define QUANTUM_CHESS_PROJ_BISHOP_H

#include <iostream>
#include "chessman.h"
#include "../position.h"

class Bishop: public Chessman {
private:
    std::string print() const override;
    
public:
    Bishop(const Position & position, bool white_, Board & board_);
    
    void calculatePosibleMoves(const Position &initial, std::vector<Position> &posible_moves) const override;

    ~Bishop() override = default;
};


#endif //QUANTUM_CHESS_PROJ_BISHOP_H
