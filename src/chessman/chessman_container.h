#ifndef QUANTUM_CHESS_PROJ_CHESSMAN_CONTAINER_H
#define QUANTUM_CHESS_PROJ_CHESSMAN_CONTAINER_H

#include "chessman.h"

class Chessman;
class Board;

// Contenedor RAII de chessman
class ChessmanContainer {
    Chessman * pointer;

public:
    ChessmanContainer(char chessman_, Position position, bool white, Board &board);

    ChessmanContainer(const ChessmanContainer &) = delete;

    ChessmanContainer(ChessmanContainer && orig);

    ChessmanContainer & operator=(const ChessmanContainer &) = delete;

    ChessmanContainer & operator=(ChessmanContainer && orig);

    ~ChessmanContainer();

    Chessman * get();
};


#endif //QUANTUM_CHESS_PROJ_CHESSMAN_CONTAINER_H
