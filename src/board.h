#ifndef QUANTUM_CHESS_PROJ_BOARD_H
#define QUANTUM_CHESS_PROJ_BOARD_H

#include <map>
#include "position.h"
#include "chessman/chessman.h"
#include "chessman/chessman_container.h"
#include <vector>

class Chessman;
class ChessmanContainer;

class Board {
    std::vector<ChessmanContainer> chessmen;
    // TODO CAMBIAR POR CHESSMAN &?
    std::map<const Position, Chessman *> board;
    bool next_white;

public:
    Board();

    void move(const Position & initial, const Position & final);

    Chessman * getChessmanAt(const Position & position);

    void removeChessmanOf(const Position &position);

    void addChessmanOfIn(const Position &initial, const Position &final);

    void load();

    void addChessman(ChessmanContainer &&chessman_cont);

    bool nextWhite() const;
};


#endif //QUANTUM_CHESS_PROJ_BOARD_H
