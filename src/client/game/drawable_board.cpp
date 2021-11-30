#include "drawable_board.h"
#include "../communication/client_protocol.h"
#include "../communication/chessman_data.h"
#include "drawable_tile.h"
#include "../sdl/renderer.h"
#include <map>
#include <utility>
#include <string>

#define BACKGROUND_TRANSPARENCY 0.4

DrawableBoard::DrawableBoard(Window &window, const std::string &image,
                             int width, int height) : renderer(
    window.renderer()),
                                                      background(
                                                          window.renderer(),
                                                          image,
                                                          width,
                                                          height),
                                                      chessman_repository(
                                                          renderer),
                                                      tile_repository(
                                                          renderer) {
  background.setBlendMode(SDL_BLENDMODE_BLEND);
  background.setAlpha(BACKGROUND_TRANSPARENCY);
  for (size_t i = 0; i < 8; i++) {
    for (size_t j = 0; j < 8; j++) {
      const Position position(i, j);
      DrawableTile tile(renderer, position.isEven(), tile_repository);
      board.insert(std::move(std::pair<const Position, DrawableTile>(position,
                                                                     std::move(
                                                                         tile))));
    }
  }
}

// TODO borrar
void DrawableBoard::render() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  for (auto &it: board) {
    it.second.render(it.first.x(), it.first.y());
  }
  for (auto &it: chessmen) {
    it.second.render(it.first.x(), it.first.y());
  }
}

void DrawableBoard::load(std::vector<ChessmanData> &chessman_data_vector) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  chessmen.clear();
  for (auto &chessman_data: chessman_data_vector) {
    DrawableChessman chessman(renderer, chessman_repository, chessman_data);
    chessmen.insert(std::pair<const Position, DrawableChessman>
                        (chessman_data.position,
                         std::move(chessman)));
  }
}

void DrawableBoard::moveTile(const Position &pos) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (board.count(pos))
    board.at(pos).loadTile(TileSpriteRepository::TILE_MOVE);
}

void DrawableBoard::quantumTile(const Position &pos) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (board.count(pos))
    board.at(pos).loadTile(TileSpriteRepository::TILE_QUANTUM);
}

void DrawableBoard::entangledTile(const Position &pos) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (board.count(pos))
    board.at(pos).loadTile(TileSpriteRepository::TILE_ENTANGLED);
}

void DrawableBoard::splitTile(const Position &pos) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (board.count(pos))
    board.at(pos).loadTile(TileSpriteRepository::TILE_SPLIT);
}

void DrawableBoard::mergeTile(const Position &pos) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (board.count(pos))
    board.at(pos).loadTile(TileSpriteRepository::TILE_MERGE);
}

void DrawableBoard::setDefault() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  for (auto &it: board) {
    it.second.loadTile(TileSpriteRepository::TILE_DEFAULT);
  }
}

std::map<const Position, DrawableTile> DrawableBoard::getTiles() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return board;
}

std::map<const Position, DrawableChessman> DrawableBoard::getChessmen() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return chessmen;
}

TextureSprite &DrawableBoard::getBackground() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return background;
}

void DrawableBoard::render(CoordinateTransformer &transformer, int width,
                           int height) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  for (auto &tile: board) {
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
