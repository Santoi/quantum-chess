#ifndef QUANTUM_CHESS_PROJ_CHESSMAN_H
#define QUANTUM_CHESS_PROJ_CHESSMAN_H

#include "../sdl/renderer.h"
#include "../sdl/texture_sprite.h"
#include "../communication/chessman_data.h"
#include "../sdl/chessman_sprite_repository.h"
#include <map>
#include <string>

class Renderer;

class Chessman {
private:
  Renderer &renderer;
  TextureSprite & sprite_;
  TextureSprite & fill;
  double probability;

public:
  Chessman(Renderer &renderer, ChessmanSpriteRepository & repository,
           const ChessmanData &data);
  Chessman(Chessman &&other) noexcept;
  Chessman(const Chessman &other) = delete;
  Chessman& operator=(Chessman &&other) noexcept;
  void render(int x, int y);
  ~Chessman();
};


#endif //QUANTUM_CHESS_PROJ_CHESSMAN_H
