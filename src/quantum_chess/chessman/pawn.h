#ifndef QUANTUM_CHESS_PROJ_PAWN_H
#define QUANTUM_CHESS_PROJ_PAWN_H

#include <vector>
#include <string>
#include "chessman.h"
#include "../position.h"

class Pawn: public Chessman {
private:
    bool first_move;

    std::string print() const override;

public:
    Pawn(const Position & position, bool white_, Board & board_);

    void move(const Position & initial, const Position & final) override;

    void calculateMoves(const Position &initial,
                        std::vector<Position> &posible_moves)
                               const override;

    ~Pawn() override = default;

    virtual void calculatePosibleSplits(const Position &initial,
                                        std::vector<Position> &posible_moves);

    virtual void calculatePosibleMerges(const Position &initial,
                                        std::vector<Position> &posible_moves);
};


#endif //QUANTUM_CHESS_PROJ_PAWN_H
