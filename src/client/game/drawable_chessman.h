#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_CHESSMAN_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_CHESSMAN_H

#include "../sdl/renderer.h"
#include "../sdl/texture_sprite.h"
#include "../communication/chessman_data.h"
#include "../sdl/chessman_sprite_repository.h"
#include <map>
#include <string>

class Renderer;

class DrawableChessman {
private:
  Renderer &renderer;
  TextureSprite & sprite_;
  TextureSprite & fill;
  double probability;

public:
  DrawableChessman(Renderer &renderer, ChessmanSpriteRepository & repository,
                   const ChessmanData &data);
  DrawableChessman(DrawableChessman &&other) noexcept;
  DrawableChessman(const DrawableChessman &other) = delete;
  DrawableChessman& operator=(DrawableChessman &&other) noexcept;
  void render(int x, int y);
  ~DrawableChessman();
};


#endif //QUANTUM_CHESS_PROJ_DRAWABLE_CHESSMAN_H
