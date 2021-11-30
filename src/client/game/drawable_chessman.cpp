#include "drawable_chessman.h"
#include "../sdl/chessman_sprite_repository.h"
#include <utility>

DrawableChessman::DrawableChessman(Renderer &renderer,
                                   ChessmanSpriteRepository &repository,
                                   const ChessmanData &data) :
    renderer(&renderer),
    sprite_(&repository.getChessman(data.chessman)),
    fill(&repository.getFill(data.chessman)),
    probability(data.probability) {}

DrawableChessman::DrawableChessman(DrawableChessman &&other) noexcept: renderer(
    other.renderer),
                                                                       sprite_(
                                                                           other.sprite_),
                                                                       fill(
                                                                           other.fill),
                                                                       probability(
                                                                           other.probability) {}

DrawableChessman &
DrawableChessman::operator=(DrawableChessman &&other) noexcept {
  renderer = std::move(other.renderer);
  sprite_ = std::move(other.sprite_);
  probability = other.probability;
  return *this;
}

void DrawableChessman::render(int x, int y) {
  int size = renderer->getMinDimension() / 10;
  int ref_height = fill->getImageHeight();
  int dh = size - size * probability;
  int dy = ref_height - ref_height * probability;
  fill->render(0, dy, x, y + dh, ref_height, ref_height * probability,
               size, size - dh);
  sprite_->render(x, y, size, size);
}

DrawableChessman::~DrawableChessman() = default;
