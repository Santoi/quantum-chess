#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_CHESS_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_CHESS_H


#include "../sdl/coordinate_transformer.h"

class Board;

class DrawableChess {
  Board &board;

public:
  explicit DrawableChess(Board &board);

  void render(CoordinateTransformer &transformer, int width,
              int height);

};


#endif //QUANTUM_CHESS_PROJ_DRAWABLE_CHESS_H
