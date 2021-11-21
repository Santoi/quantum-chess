#ifndef QUANTUM_CHESS_PROJ_QUEEN_H
#define QUANTUM_CHESS_PROJ_QUEEN_H

#include <vector>
#include <string>
#include "chessman.h"
#include "../position.h"

class Queen: public Chessman {
private:
    char print() const override;
    
public:
    Queen(const Position & position, bool white_, Board & board_);
    
    void calculateMoves(const Position &initial,
                        std::list<Position> &posible_moves)
                               const override;

    ~Queen() override = default;
};


#endif //QUANTUM_CHESS_PROJ_QUEEN_H
