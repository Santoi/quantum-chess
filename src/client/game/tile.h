#ifndef QUANTUM_CHESS_PROJ_TILE_H
#define QUANTUM_CHESS_PROJ_TILE_H

#include "../sdl/renderer.h"
#include "../sdl/texture_sprite.h"
#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <string>

class Tile {
private:
  Renderer &renderer;
  TextureSprite sprite_;
  std::map<int, std::string> images;

public:
  typedef enum {
    TILE_DEFAULT,
    TILE_MOVE,
    TILE_ENTANGLED,
    TILE_QUANTUM,
    TILE_SPLIT,
    TILE_MERGE
  } TileType;
  void loadTile(TileType type);

  Tile(Renderer &renderer, bool black);
  Tile(Tile &&other) noexcept;
  Tile(const Tile &other) = delete;
  Tile& operator=(Tile &&other) noexcept;
  void render(int x, int y);
};


#endif //QUANTUM_CHESS_PROJ_TILE_H
