#ifndef QUANTUM_CHESS_PROJ_BOARD_H
#define QUANTUM_CHESS_PROJ_BOARD_H

#include <map>
#include "position.h"
#include "chessman.h"
#include <vector>

class Chessman;

class Board {
    std::vector<Chessman> chessmen;
    std::map<const Position, Chessman *> board;

public:
    Board();

    void move(const Position & initial, const Position & final);

    Chessman * getChessmanAt(const Position & position);
};


#endif //QUANTUM_CHESS_PROJ_BOARD_H
