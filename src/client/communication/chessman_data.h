#ifndef QUANTUM_CHESS_PROJ_CHESSMAN_DATA_H
#define QUANTUM_CHESS_PROJ_CHESSMAN_DATA_H


#include "../game/board_position.h"
#include <string>

typedef struct ChessmanData {
  const BoardPosition position;
  const std::string chessman;
  const double probability;

  ChessmanData(const BoardPosition &position_, std::string chessman_,
               double prob);
} ChessmanData;


#endif //QUANTUM_CHESS_PROJ_CHESSMAN_DATA_H
