#ifndef QUANTUM_CHESS_PROJ_SQUARE_DATA_H
#define QUANTUM_CHESS_PROJ_SQUARE_DATA_H

#include "position.h"

typedef struct SquareData {
public:
  const char chessman;
  const bool white;
  const Position position;
  const double probability;

  SquareData(char chessman_, bool white_, const Position &position_,
             double probability_);
} SquareData;


#endif //QUANTUM_CHESS_PROJ_SQUARE_DATA_H
