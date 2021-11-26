#include "tile.h"
#include "../sdl/tile_sprite_repository.h"

Tile::Tile(Renderer &renderer, bool black_, TileSpriteRepository & repository) :
           renderer(renderer),
           sprite_(&repository.getTile(TileSpriteRepository::TILE_DEFAULT, black_)),
           repository(repository), black(black_) {}

Tile::Tile(Tile &&other) noexcept: renderer(other.renderer),
                                   sprite_(other.sprite_),
                                   repository(other.repository), black(other.black) {}

void Tile::render(int x, int y) {
  int size = renderer.getMinDimension() / 10;
  sprite_->render(x, y, size, size);
}

void Tile::loadTile(TileSpriteRepository::TileType type) {
  sprite_ = &repository.getTile(type, black);
}
