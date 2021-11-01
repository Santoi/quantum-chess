#ifndef QUANTUM_CHESS_PROJ_CHESSMAN_H
#define QUANTUM_CHESS_PROJ_CHESSMAN_H


#include "position.h"


// Primera version.
// TODO luego validar con el tablero.
// TODO luego hacer comer.
// TODO validar con color.

class Chessman {
protected:
    Position position;
public:
    explicit Chessman(const Position & position_);

    virtual void move(const Position & new_position) = 0;

    virtual bool canMove(const Position & new_position) = 0;
};

class Pawn: public Chessman {
    bool first_move;
public:
    explicit Pawn(const Position & position_);

    void move(const Position & new_position) override;

    bool canMove(const Position &new_position) override;
};


#endif //QUANTUM_CHESS_PROJ_CHESSMAN_H
