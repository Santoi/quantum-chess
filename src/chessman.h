#ifndef QUANTUM_CHESS_PROJ_CHESSMAN_H
#define QUANTUM_CHESS_PROJ_CHESSMAN_H

#include <vector>
#include "position.h"
#include "quantum_position_tree.h"
#include "board.h"


#define MAX_PATH_LENGTH 8

// Primera version.
// TODO luego validar con el tablero.
// TODO luego hacer comer.
// TODO validar con color.
// TODO CHEQUEAR SI TODOS LOS QUE ESTAN EN EL MEDIO SUMAN 100 % PROBA.

class Board;

class Chessman {
protected:
    QuantumPositionTree tree;
    Board & board;
    bool white;

    bool checkFreeMove(const std::vector<Position> & path,
                       std::vector<Chessman *> * chessmen);

    virtual bool checkMiddleChessmen(const Position &initial,
                                     const Position & final,
                                     std::vector<Chessman *> *
                                             chessmen_in_path) = 0;


public:
    Chessman(const Position & position_, bool white_, Board & board_);

    virtual void move(const Position & initial, const Position & final);

    bool canMove(const Position & initial, const Position & final);

    bool isQuantum() const;
};

class Pawn: public Chessman {
    bool first_move;

    bool checkMiddleChessmen(const Position &initial, const Position & final,
                             std::vector<Chessman *> * chessmen_in_path)
                             override;
public:
    explicit Pawn(const Position & position_, bool white_, Board & board_);

    void move(const Position & initial, const Position & final) override;
};


#endif //QUANTUM_CHESS_PROJ_CHESSMAN_H
