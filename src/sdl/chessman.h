#ifndef QUANTUM_CHESS_PROJ_CHESSMAN_H
#define QUANTUM_CHESS_PROJ_CHESSMAN_H

#include "renderer.h"
#include "sprite.h"

class Renderer;

class Chessman {
private:
  Renderer &renderer;
  Sprite sprite_;

public:
  Chessman(Renderer &renderer, char chessman);
  Chessman(Chessman &&other) noexcept;
  Chessman(const Chessman &other) = delete;
  Chessman& operator=(Chessman &&other) noexcept;
  void render(int x, int y);
  ~Chessman();
};


#endif //QUANTUM_CHESS_PROJ_CHESSMAN_H
