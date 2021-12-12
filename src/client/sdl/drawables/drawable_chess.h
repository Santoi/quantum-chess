#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_CHESS_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_CHESS_H


#include "../coordinate_transformer.h"

class DrawableBoard;

class DrawableChess {
  DrawableBoard &board;

public:
  explicit DrawableChess(DrawableBoard &board);

  void render(CoordinateTransformer &transformer, int width,
              int height);

};


#endif //QUANTUM_CHESS_PROJ_DRAWABLE_CHESS_H
