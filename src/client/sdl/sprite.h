#ifndef QUANTUM_CHESS_PROJ_SPRITE_H
#define QUANTUM_CHESS_PROJ_SPRITE_H

#include "renderer.h"

class Renderer;

class Sprite {
protected:
  Renderer &renderer;

public:
  explicit Sprite(Renderer &renderer);
};


#endif //QUANTUM_CHESS_PROJ_SPRITE_H
