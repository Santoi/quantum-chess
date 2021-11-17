#include "chessman.h"
#include <utility>

Chessman::Chessman(Renderer &renderer, char chessman): renderer(renderer),
                                                       sprite_(renderer, "img/falcon.png",
                                           renderer.getMinDimension() / 10,
                                           renderer.getMinDimension() / 10) {
  switch (chessman) {
    case 't':
      sprite_.loadImage("img/tower.png");
      break;
    case 'k':
      sprite_.loadImage("img/knight.png");
      break;
    case 'b':
      sprite_.loadImage("img/bishop.png");
      break;
    case 'K':
      sprite_.loadImage("img/king.png");
      break;
    case 'q':
      sprite_.loadImage("img/queen.png");
      break;
    case 'p':
      sprite_.loadImage("img/pawn.png");
      break;
    default:
      break;
  }
}

Chessman::Chessman(Chessman &&other) noexcept: renderer(other.renderer),
                                      sprite_(std::move(other.sprite_)) {}

Chessman& Chessman::operator=(Chessman &&other) noexcept {
  renderer = std::move(other.renderer);
  sprite_ = std::move(other.sprite_);
  return *this;
}

void Chessman::render(int x, int y) {
  int size = renderer.getMinDimension() / 10;
  sprite_.render(x, y, size, size);
}

Chessman::~Chessman() = default;
