#ifndef QUANTUM_CHESS_PROJ_KNIGHT_H
#define QUANTUM_CHESS_PROJ_KNIGHT_H

#include <vector>
#include <string>
#include "chessman.h"
#include "../position.h"

class Knight: public Chessman {
private:
    std::string print() const override;

public:
    Knight(const Position & position, bool white_, Board & board_);
    
    void calculatePosibleMoves(const Position &initial,
                               std::vector<Position> &posible_moves)
                               const override;

    void calculatePath(const Position &initial, const Position &final,
                       std::vector<Position> &path) const override;

    ~Knight() override = default;
};


#endif //QUANTUM_CHESS_PROJ_KNIGHT_H
