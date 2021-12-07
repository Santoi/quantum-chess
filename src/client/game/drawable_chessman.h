#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_CHESSMAN_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_CHESSMAN_H

#include "../communication/chessman_data.h"
#include "../sdl/sprite_repositories/chessman_sprite_repository.h"
#include "../sdl/texture_sprite.h"
#include "../sdl/renderer.h"
#include <map>
#include <string>

class Renderer;

class ChessmanSpriteRepository;

class DrawableChessman {
private:
  Renderer *renderer;
  TextureSprite *sprite_;
  TextureSprite *fill;
  double probability;

public:
  DrawableChessman(Renderer &renderer, ChessmanSpriteRepository &repository,
                   const ChessmanData &data);

  DrawableChessman(DrawableChessman &&other) noexcept;

  DrawableChessman(const DrawableChessman &other) = default;

  DrawableChessman &operator=(DrawableChessman &&other) noexcept;

  DrawableChessman &operator=(const DrawableChessman &other) = default;

  void render(int x, int y);

  ~DrawableChessman();
};


#endif //QUANTUM_CHESS_PROJ_DRAWABLE_CHESSMAN_H
