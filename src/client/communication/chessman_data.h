#ifndef QUANTUM_CHESS_PROJ_CHESSMAN_DATA_H
#define QUANTUM_CHESS_PROJ_CHESSMAN_DATA_H


#include "../position.h"

typedef struct ChessmanData {
    const Position position;
    const std::string chessman;
    const double probability;

    ChessmanData(const Position & position_, std::string chessman_,
                 double prob);
} ChessmanData;


#endif //QUANTUM_CHESS_PROJ_CHESSMAN_DATA_H
