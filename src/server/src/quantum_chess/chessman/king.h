#ifndef QUANTUM_CHESS_PROJ_KING_H
#define QUANTUM_CHESS_PROJ_KING_H

#include <vector>
#include <string>
#include "chessman.h"
#include "../position.h"

class King: public Chessman {
private:
    char print() const override;
    
public:
    King(const Position & position, bool white_, Board & board_);
    
    void calculateMoves(const Position &initial,
                        std::list<Position> &posible_moves)
                               const override;

    ~King() override = default;
};


#endif //QUANTUM_CHESS_PROJ_KING_H
