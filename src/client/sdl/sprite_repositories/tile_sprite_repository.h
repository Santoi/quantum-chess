#ifndef QUANTUM_CHESS_PROJ_TILE_SPRITE_REPOSITORY_H
#define QUANTUM_CHESS_PROJ_TILE_SPRITE_REPOSITORY_H

#include <map>
#include "../texture_sprite.h"

class TileSpriteRepository {
public:
  typedef enum {
    TILE_DEFAULT,
    TILE_MOVE,
    TILE_ENTANGLED,
    TILE_QUANTUM,
    TILE_SPLIT,
    TILE_MERGE,
    TILE_SELECTED,
  } TileType;

private:
  std::map<TileType, TextureSprite> white_tiles;
  std::map<TileType, TextureSprite> black_tiles;

  // Load white tiles sprites
  void loadWhite(Renderer &renderer);

  // Load black tiles sprites
  void loadBlack(Renderer &renderer);

public:
  explicit TileSpriteRepository(Renderer &renderer);

  // Get the TileType sprite
  TextureSprite &getTile(TileType type, bool black);
};


#endif //QUANTUM_CHESS_PROJ_TILE_SPRITE_REPOSITORY_H
