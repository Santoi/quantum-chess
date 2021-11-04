#ifndef QUANTUM_CHESS_PROJ_ASCII_CHESS_H
#define QUANTUM_CHESS_PROJ_ASCII_CHESS_H

#include "board.h"

class AsciiChess {
    Board & board;

public:
    explicit AsciiChess(Board & board);

    void draw();

    void readCommand(std::string first, std::string second, std::string third, std::string forth, std::string fifth);
};


#endif //QUANTUM_CHESS_PROJ_ASCII_CHESS_H
