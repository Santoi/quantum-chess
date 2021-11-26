#ifndef QUANTUM_CHESS_PROJ_SPRITE_H
#define QUANTUM_CHESS_PROJ_SPRITE_H

#include "renderer.h"

class Renderer;

class Sprite {
protected:
  Renderer &renderer;
  int width_, height_;

public:
  explicit Sprite(Renderer &renderer, int width = 0, int height = 0);

  int width() const;

  int height() const;
};


#endif //QUANTUM_CHESS_PROJ_SPRITE_H
