#ifndef QUANTUM_CHESS_PROJ_TOWER_H
#define QUANTUM_CHESS_PROJ_TOWER_H

#include "chessman.h"
#include "../position.h"

class Tower: public Chessman {
private:
    std::string print() const override;

public:
    Tower(const Position & position, bool white_, Board & board_);
    void calculatePosibleMoves(const Position &initial, std::vector<Position> &posible_moves) const override;

    ~Tower() override = default;
};


#endif //QUANTUM_CHESS_PROJ_TOWER_H
