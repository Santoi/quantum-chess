#include "tile_sprite_repository.h"
#include "../drawables/drawable_tile.h"
#include <map>
#include <string>

#define BOARD_PATH "resources/sprites/board/"

TileSpriteRepository::TileSpriteRepository(Renderer &renderer) : white_tiles(),
                                                                 black_tiles() {
  loadWhite(renderer);
  loadBlack(renderer);
}

TextureSprite &
TileSpriteRepository::getTile(TileSpriteRepository::TileType type, bool black) {
  if (black)
    return black_tiles.at(type);
  return white_tiles.at(type);
}

void TileSpriteRepository::loadWhite(Renderer &renderer) {
  std::map<TileType, std::string> images = {
          {TILE_DEFAULT,   BOARD_PATH "white_square.png"},
          {TILE_MOVE,      BOARD_PATH "white_square_move.png"},
          {TILE_ENTANGLED, BOARD_PATH "white_square_entangled.png"},
          {TILE_QUANTUM,   BOARD_PATH "white_square_quantum.png"},
          {TILE_SPLIT,     BOARD_PATH "white_square_split.png"},
          {TILE_MERGE,     BOARD_PATH "white_square_merge.png"},
          {TILE_SELECTED,  BOARD_PATH "current_tile.png"},
  };
  for (auto &pair: images) {
    // TODO: renderer.getHeight() maybe?
    TextureSprite tile(renderer, pair.second,
                       renderer.getMinDimension() / 10,
                       renderer.getMinDimension() / 10);
    white_tiles.insert(std::make_pair(pair.first, std::move(tile)));
  }
}

void TileSpriteRepository::loadBlack(Renderer &renderer) {
  std::map<TileType, std::string> images = {
          {TILE_DEFAULT,   BOARD_PATH "black_square.png"},
          {TILE_MOVE,      BOARD_PATH "black_square_move.png"},
          {TILE_ENTANGLED, BOARD_PATH "black_square_entangled.png"},
          {TILE_QUANTUM,   BOARD_PATH "black_square_quantum.png"},
          {TILE_SPLIT,     BOARD_PATH "black_square_split.png"},
          {TILE_MERGE,     BOARD_PATH "black_square_merge.png"},
          {TILE_SELECTED,  BOARD_PATH "current_tile.png"},
  };
  for (auto &pair: images) {
    TextureSprite tile(renderer, pair.second,
                       renderer.getMinDimension() / 10,
                       renderer.getMinDimension() / 10);
    black_tiles.insert(std::make_pair(pair.first, std::move(tile)));
  }
}
