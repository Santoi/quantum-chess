#include "drawable_tile.h"
#include "../sdl/sprite_repositories/tile_sprite_repository.h"

DrawableTile::DrawableTile(Renderer &renderer, bool black_,
                           TileSpriteRepository &repository) :
    renderer(&renderer),
    sprite_(&repository.getTile(TileSpriteRepository::TILE_DEFAULT, black_)),
    repository(&repository), black(black_) {}

DrawableTile::DrawableTile(DrawableTile &&other) noexcept: renderer(
    other.renderer),
                                                           sprite_(
                                                               other.sprite_),
                                                           repository(
                                                               other.repository),
                                                           black(other.black) {}

void DrawableTile::render(int x, int y) {
  int size = renderer->getMinDimension() / 10;
  sprite_->render(x, y, size, size);
}

void DrawableTile::loadTile(TileSpriteRepository::TileType type) {
  sprite_ = &repository->getTile(type, black);
}
