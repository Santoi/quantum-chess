#include "tile.h"

Tile::Tile(Renderer &renderer, bool black) : renderer(renderer),
                                             sprite_(renderer, "img/falcon.png",
                                                     renderer.getMinDimension() / 10,
                                                     renderer.getMinDimension() / 10) {
  if (black) {
    images = {
        {DEFAULT,   "img/black_square.png"},
        {MOVE,      "img/black_square_move.png"},
        {ENTANGLED, "img/black_square_entangle.png"},
        {QUANTUM,   "img/black_square_split.png"}
    };
  } else {
    images = {
        {DEFAULT,   "img/white_square.png"},
        {MOVE,      "img/white_square_move.png"},
        {ENTANGLED, "img/white_square_relation.png"},
        {QUANTUM,   "img/white_square_split.png"}
    };
  }
  sprite_.loadImage(images[DEFAULT]);
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

void Tile::loadDefault() {
  sprite_.loadImage(images[DEFAULT]);
}

void Tile::loadMove() {
  sprite_.loadImage(images[MOVE]);
}

void Tile::loadEntagled() {
  sprite_.loadImage(images[ENTANGLED]);
}

void Tile::loadQuantum() {
  sprite_.loadImage(images[QUANTUM]);
}
