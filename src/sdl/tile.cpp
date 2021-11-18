#include "tile.h"

Tile::Tile(Renderer &renderer, bool black) :
           renderer(renderer),
           sprite_(renderer, "img/falcon.png",
                   renderer.getMinDimension() / 10,
                   renderer.getMinDimension() / 10) {
  if (black) {
    images = {
        {TILE_DEFAULT,   "img/black_square.png"},
        {TILE_MOVE,      "img/black_square_move.png"},
        {TILE_ENTANGLED, "img/black_square_entangled.png"},
        {TILE_QUANTUM, "img/black_square_quantum.png"},
        {TILE_SPLIT, "img/black_square_split.png"},
        {TILE_MERGE, "img/black_square_merge.png"}
    };
  } else {
    images = {
        {TILE_DEFAULT,   "img/white_square.png"},
        {TILE_MOVE,      "img/white_square_move.png"},
        {TILE_ENTANGLED, "img/white_square_entangled.png"},
        {TILE_QUANTUM, "img/white_square_quantum.png"},
        {TILE_SPLIT, "img/white_square_split.png"},
        {TILE_MERGE, "img/white_square_merge.png"}
    };
  }
  sprite_.loadImage(images[TILE_DEFAULT]);
}

Tile::Tile(Tile &&other) noexcept: renderer(other.renderer),
                                   sprite_(std::move(other.sprite_)),
                                   images(std::move(other.images)) {}

void Tile::render(int x, int y) {
  int size = renderer.getMinDimension() / 10;
  sprite_.render(x, y, size, size);
}

Tile& Tile::operator=(Tile &&other) noexcept {
  renderer = std::move(other.renderer);
  sprite_ = std::move(other.sprite_);
  images = std::move(other.images);
  return *this;
}

void Tile::loadTile(TileType type) {
  sprite_.loadImage(images[type]);
}
