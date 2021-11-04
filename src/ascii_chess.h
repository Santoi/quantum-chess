#ifndef QUANTUM_CHESS_PROJ_ASCII_CHESS_H
#define QUANTUM_CHESS_PROJ_ASCII_CHESS_H

#include "board.h"

class AsciiChess {
    Board & board;

public:
    explicit AsciiChess(Board & board);

    void draw();

    bool readCommand();
};


#endif //QUANTUM_CHESS_PROJ_ASCII_CHESS_H
