#include "tile_sprite_repository.h"
#include "../game/drawable_tile.h"

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
      {TILE_DEFAULT,   "img/white_square.png"},
      {TILE_MOVE,      "img/white_square_move.png"},
      {TILE_ENTANGLED, "img/white_square_entangled.png"},
      {TILE_QUANTUM,   "img/white_square_quantum.png"},
      {TILE_SPLIT,     "img/white_square_split.png"},
      {TILE_MERGE,     "img/white_square_merge.png"}
  };
  for (auto &pair: images) {
    TextureSprite tile(renderer, pair.second,
                       renderer.getMinDimension() / 10,
                       renderer.getMinDimension() / 10);
    white_tiles.insert(std::make_pair(pair.first, std::move(tile)));
  }
}

void TileSpriteRepository::loadBlack(Renderer &renderer) {
  std::map<TileType, std::string> images = {
      {TILE_DEFAULT,   "img/black_square.png"},
      {TILE_MOVE,      "img/black_square_move.png"},
      {TILE_ENTANGLED, "img/black_square_entangled.png"},
      {TILE_QUANTUM,   "img/black_square_quantum.png"},
      {TILE_SPLIT,     "img/black_square_split.png"},
      {TILE_MERGE,     "img/black_square_merge.png"}
  };
  for (auto &pair: images) {
    TextureSprite tile(renderer, pair.second,
                       renderer.getMinDimension() / 10,
                       renderer.getMinDimension() / 10);
    black_tiles.insert(std::make_pair(pair.first, std::move(tile)));
  }
}
