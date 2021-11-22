#ifndef QUANTUM_CHESS_PROJ_TILE_H
#define QUANTUM_CHESS_PROJ_TILE_H

#include "../sdl/sprite.h"
#include "../sdl/renderer.h"
#include "../sdl/tile_sprite_repository.h"
#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <string>

class Tile {
private:
  Renderer &renderer;
  Sprite * sprite_;
  TileSpriteRepository & repository;
  bool black;

public:
  void loadTile(TileSpriteRepository::TileType type);

  Tile(Renderer &renderer, bool black_, TileSpriteRepository & repository);
  Tile(Tile &&other) noexcept;
  Tile(const Tile &other) = delete;
  Tile& operator=(Tile &&other) noexcept = delete;
  void render(int x, int y);
};


#endif //QUANTUM_CHESS_PROJ_TILE_H
