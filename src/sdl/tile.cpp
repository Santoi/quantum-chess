#include "tile.h"

Tile::Tile(SDL2pp::Renderer &renderer, bool black) : renderer(renderer),
                                                     sprite(renderer) {
  if (black) {
    images = {
        {DEFAULT, "img/black_square.png"},
        {MOVE, "img/black_square_move.png"},
        {ENTANGLE, "img/black_square_entangle.png"},
        {SPLIT, "img/black_square_split.png"}
    };
  } else {
    images = {
        {DEFAULT, "img/white_square.png"},
        {MOVE, "img/white_square_move.png"},
        {ENTANGLE, "img/white_square_relation.png"},
        {SPLIT, "img/white_square_split.png"}
    };
  }
  sprite.loadImage(images[DEFAULT]);
}

Tile::Tile(Tile &&other) noexcept: renderer(other.renderer),
                                   sprite(std::move(other.sprite)),
                                   images(std::move(other.images)) {}

void Tile::render(int x_pos, int y_pos) {
  int width, height;
  width = height = renderer.GetOutputHeight() / 10;
  int middle_board = std::min(renderer.GetOutputHeight(),
                                                renderer.GetOutputWidth()) / 2;
  x_pos -= 4;
  y_pos -= 3;
  x_pos *= width;
  y_pos *= -height;
  sprite.render(middle_board + x_pos, middle_board + y_pos, width, height);
}

void Tile::loadDefault() {
  sprite.loadImage(images[DEFAULT]);
}

void Tile::loadMove() {
  sprite.loadImage(images[MOVE]);
}

void Tile::loadEntagle() {
  sprite.loadImage(images[ENTANGLE]);
}

void Tile::loadSplit() {
  sprite.loadImage(images[SPLIT]);
}
