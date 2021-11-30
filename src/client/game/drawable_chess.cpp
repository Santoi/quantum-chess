#include "drawable_chess.h"
#include "../sdl/pixel_coordinate.h"
#include "board.h"

DrawableChess::DrawableChess(Board &board) : board(board) {}

void DrawableChess::render(CoordinateTransformer &transformer, int width,
                           int height) {
  //std::cerr << "cargo tiles" << std::endl;
  auto tiles = board.getTiles();
  //std::cerr << "cargo back" << std::endl;
  //TextureSprite &background = board.getBackground();
  //std::cerr << "cargo chessmen" << std::endl;
  auto chessmen = board.getChessmen();
  //std::cerr << "termine" << std::endl;

  for (auto &tile: tiles) {
    PixelCoordinate pixel(0, 0);
    transformer.position2Pixel(tile.first, pixel, width, height);
    tile.second.render(pixel.x(), pixel.y());
  }
  //background.render(0, 0, width, height);
  for (auto &chessman: chessmen) {
    PixelCoordinate pixel(0, 0);
    transformer.position2Pixel(chessman.first, pixel, width, height);
    chessman.second.render(pixel.x(), pixel.y());
  }
}
