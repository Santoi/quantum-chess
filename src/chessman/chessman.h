#ifndef QUANTUM_CHESS_PROJ_CHESSMAN_H
#define QUANTUM_CHESS_PROJ_CHESSMAN_H

#include <vector>
#include "../position.h"
#include "../quantum_position_tree.h"
#include "../board.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

#define MAX_PATH_LENGTH 8

// Primera version.
// TODO luego validar con el tablero.
// TODO luego hacer comer.
// TODO validar con color.
// TODO CHEQUEAR SI TODOS LOS QUE ESTAN EN EL MEDIO SUMAN 100 % PROBA.

class Board;

class Chessman {
protected:
    Position position;
    Board & board;
    bool white;

    bool checkFreePath(const std::vector<Position> & path) const;

    void calculatePath(const Position &initial, const Position &final, std::vector<Position> &path) const;

    void calculateFilePath(const Position &initial, const Position &final, std::vector<Position> &path) const;

    void calculateRowPath(const Position &initial, const Position &final, std::vector<Position> &path) const;

    void calculateDiagonalPath(const Position &initial, const Position final, std::vector<Position> &path) const;

    bool getPathMiddleChessmen(const std::vector<Position> &path, std::vector<Chessman *> *chessmen) const;

    virtual void checkCanMove(Position initial, Position final, std::vector<Chessman *> &chessmen_in_path) const;

    virtual std::string print() const = 0;

public:
    Chessman(const Position & position_, bool white_, Board & board_);

    virtual void move(const Position & initial, const Position & final);

    bool isQuantum() const;

    Position getPosition();

    // TODO deberia revisar la ultima posicion tambien!!! porque sino no la voy a mostrar.
    virtual void calculatePosibleMoves(const Position &initial, std::vector<Position> &posible_moves) const = 0;

    friend std::ostream & operator<<(std::ostream & os, const Chessman & chessman);
};
/*
class Pawn: public Chessman {
    bool first_move;

    bool checkMoveAndMiddleChessmen(const Position &initial,
                                    const Position & final,
                                    std::vector<Chessman *> *
                                            chessmen_in_path)
                                    override;
public:
    Pawn(const Position & position_, bool white_, Board & board_);

    void move(const Position & initial, const Position & final) override;
};

class Knight: public Chessman {
    bool checkMoveAndMiddleChessmen(const Position &initial,
                                    const Position & final,
                                    std::vector<Chessman *> * chessmen_in_path)
                                    override;
public:
    Knight(const Position & position, bool white_, Board & board_);
};*/


#endif //QUANTUM_CHESS_PROJ_CHESSMAN_H
