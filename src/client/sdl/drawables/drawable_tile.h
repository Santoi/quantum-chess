#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_TILE_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_TILE_H

#include "../renderer.h"
#include "../texture_sprite.h"
#include "../sprite_repositories/tile_sprite_repository.h"
#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <string>

class DrawableTile {
private:
  Renderer *renderer;
  TextureSprite *sprite_;
  TileSpriteRepository *repository;
  bool black;

public:
  void loadTile(TileSpriteRepository::TileType type);

  DrawableTile(Renderer &renderer, bool black_,
               TileSpriteRepository &repository);

  DrawableTile(DrawableTile &&other) noexcept;

  DrawableTile(const DrawableTile &other) = default;

  DrawableTile &operator=(const DrawableTile &other) = default;

  void render(int x, int y);
};


#endif //QUANTUM_CHESS_PROJ_DRAWABLE_TILE_H
