#include "drawable_chess.h"
#include "../sdl/pixel_coordinate.h"
#include "board.h"

DrawableChess::DrawableChess(Board &board) : board(board) {}

void DrawableChess::render(CoordinateTransformer &transformer, int width,
                           int height) {
  auto tiles = board.getTiles();
  TextureSprite &background = board.getBackground();
  auto chessmen = board.getChessmen();

  for (auto &tile: tiles) {
    PixelCoordinate pixel(0, 0);
    transformer.position2Pixel(tile.first, pixel, width, height);
    tile.second.render(pixel.x(), pixel.y());
  }
  background.render(0, 0, width, height);
  for (auto &chessman: chessmen) {
    PixelCoordinate pixel(0, 0);
    transformer.position2Pixel(chessman.first, pixel, width, height);
    chessman.second.render(pixel.x(), pixel.y());
  }
}
