#include "board.h"
#include "../communication/client_protocol.h"
#include "../communication/chessman_data.h"
#include "drawable_tile.h"
#include "../sdl/renderer.h"
#include <map>
#include <utility>
#include <string>

#define BACKGROUND_TRANSPARENCY 0.4

Board::Board(Window &window, const std::string &image,
             int width, int height) : renderer(window.renderer()),
                                      background(window.renderer(), image,
                                                 width,
                                                 height),
                                      chessman_repository(renderer),
                                      tile_repository(renderer) {
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
void Board::render() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  for (auto &it: board) {
    it.second.render(it.first.x(), it.first.y());
  }
  for (auto &it: chessmen) {
    it.second.render(it.first.x(), it.first.y());
  }
}

void Board::load(std::vector<ChessmanData> &chessman_data_vector) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  chessmen.clear();
  for (auto &chessman_data: chessman_data_vector) {
    DrawableChessman chessman(renderer, chessman_repository, chessman_data);
    chessmen.insert(std::pair<const Position, DrawableChessman>
                        (chessman_data.position,
                         std::move(chessman)));
  }
}

void Board::moveTile(const Position &pos) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (board.count(pos))
    board.at(pos).loadTile(TileSpriteRepository::TILE_MOVE);
}

void Board::quantumTile(const Position &pos) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (board.count(pos))
    board.at(pos).loadTile(TileSpriteRepository::TILE_QUANTUM);
}

void Board::entangledTile(const Position &pos) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (board.count(pos))
    board.at(pos).loadTile(TileSpriteRepository::TILE_ENTANGLED);
}

void Board::splitTile(const Position &pos) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (board.count(pos))
    board.at(pos).loadTile(TileSpriteRepository::TILE_SPLIT);
}

void Board::mergeTile(const Position &pos) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (board.count(pos))
    board.at(pos).loadTile(TileSpriteRepository::TILE_MERGE);
}

void Board::setDefault() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  for (auto &it: board) {
    it.second.loadTile(TileSpriteRepository::TILE_DEFAULT);
  }
}

std::map<const Position, DrawableTile> &Board::getTiles() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return board;
}

std::map<const Position, DrawableChessman> &Board::getChessmen() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return chessmen;
}

TextureSprite &Board::getBackground() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return background;
}
