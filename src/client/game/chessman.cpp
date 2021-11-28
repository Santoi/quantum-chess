#include "chessman.h"
#include "../sdl/chessman_sprite_repository.h"
#include <utility>

Chessman::Chessman(Renderer &renderer, ChessmanSpriteRepository &repository,
                   const ChessmanData &data) :
        renderer(renderer),
        sprite_(repository.getChessman(data.chessman)),
        fill(repository.getFill(data.chessman)),
        probability(data.probability) {}

Chessman::Chessman(Chessman &&other) noexcept: renderer(other.renderer),
                                               sprite_(other.sprite_),
                                               fill(other.fill),
                                               image(std::move(other.image)),
                                               probability(other.probability) {}

Chessman &Chessman::operator=(Chessman &&other) noexcept {
  renderer = std::move(other.renderer);
  sprite_ = std::move(other.sprite_);
  image = std::move(other.image);
  probability = other.probability;
  return *this;
}

void Chessman::render(int x, int y) {
  int size = renderer.getMinDimension() / 10;
  int ref_height = fill.getImageHeight();
  int dh = size - size * probability;
  int dy = ref_height - ref_height * probability;
  fill.render(0, dy, x, y + dh, ref_height, ref_height * probability,
              size, size - dh);
  sprite_.render(x, y, size, size);
}

Chessman::~Chessman() = default;
