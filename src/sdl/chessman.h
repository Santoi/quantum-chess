#ifndef QUANTUM_CHESS_PROJ_CHESSMAN_H
#define QUANTUM_CHESS_PROJ_CHESSMAN_H

#include "sprite.h"

class Chessman {
private:
  SDL2pp::Renderer &renderer;
  Sprite sprite;
  int x; // Board horizontal position [-4, 4]
  int y; // Board vertical position [-4, 4]
  // (0, 0) is center board
  int width;
  int height;

public:
  Chessman(SDL2pp::Renderer &renderer, char chessman);
  void drawAt(int x, int y);
  ~Chessman();
};


#endif //QUANTUM_CHESS_PROJ_CHESSMAN_H
