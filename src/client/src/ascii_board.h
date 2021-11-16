#ifndef QUANTUM_CHESS_PROJ_ASCII_BOARD_H
#define QUANTUM_CHESS_PROJ_ASCII_BOARD_H

#include <map>
#include <vector>
#include "position.h"

// Clase que ejecuta el ajedrez en formato ASCII.
class AsciiBoard {
    std::map<Position, char> board;
public:
    AsciiBoard();

    void draw();

    void load(std::vector<Position> & positions, std::vector<char> & character);
};


#endif //QUANTUM_CHESS_PROJ_ASCII_BOARD_H
