#include "drawable_board.h"
#include "../../communication/client_protocol.h"
#include "../../communication/chessman_data.h"
#include "drawable_tile.h"
#include "../renderer.h"
#include <map>
#include <utility>
#include <string>
#include <vector>

#define BACKGROUND_TRANSPARENCY 0.4
#define BACKGROUND_SPRITE "resources/sprites/background/stars.jpg"

DrawableBoard::DrawableBoard(Window &window, int width, int height,
                             Font &font) :
        renderer(window.renderer()),
        background(window.renderer(), BACKGROUND_SPRITE, width,
                   height),
        chessmen(), board(), positions(),
        chessman_repository(renderer),
        tile_repository(renderer),
        text_repository(renderer, font),
        current(false),
        current_tile(std::make_pair(BoardPosition(),
                                    DrawableTile(renderer, true,
                                                 tile_repository))) {
  background.setBlendMode(SDL_BLENDMODE_BLEND);
  background.setAlpha(BACKGROUND_TRANSPARENCY);
  current_tile.second.loadTile(TileSpriteRepository::TILE_SELECTED);
  // Board initialize
  for (size_t i = 0; i < 8; i++) {
    std::string num(std::to_string(i + 1));
    char c = 'A' + i;
    char l[] = {c, '\0'};
    std::string letter(l);
    DrawableText numbers(text_repository, num, 't');
    DrawableText letters(text_repository, letter, 't');
    BoardPosition row(8, i);
    BoardPosition column(i, -1);
    positions.insert(
        std::pair<const BoardPosition, DrawableText>(row, std::move(numbers)));
    positions.insert(
        std::pair<const BoardPosition, DrawableText>(column,
                                                     std::move(letters)));
    for (size_t j = 0; j < 8; j++) {
      const BoardPosition position(i, j);
      DrawableTile tile(renderer, position.isEven(), tile_repository);
      board.insert(std::pair<const BoardPosition, DrawableTile>(position,
                                                                std::move(
                                                                    tile)));
    }
  }
}

void DrawableBoard::load(std::vector<ChessmanData> &chessman_data_vector) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  chessmen.clear();
  for (auto &chessman_data: chessman_data_vector) {
    DrawableChessman chessman(renderer, chessman_repository, chessman_data);
    chessmen.insert(std::pair<const BoardPosition, DrawableChessman>
                        (chessman_data.position,
                         std::move(chessman)));
  }
}

void DrawableBoard::moveTile(const BoardPosition &pos) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (board.count(pos))
    board.at(pos).loadTile(TileSpriteRepository::TILE_MOVE);
}

void DrawableBoard::quantumTile(const BoardPosition &pos) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (board.count(pos))
    board.at(pos).loadTile(TileSpriteRepository::TILE_QUANTUM);
}

void DrawableBoard::entangledTile(const BoardPosition &pos) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (board.count(pos))
    board.at(pos).loadTile(TileSpriteRepository::TILE_ENTANGLED);
}

void DrawableBoard::splitTile(const BoardPosition &pos) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (board.count(pos))
    board.at(pos).loadTile(TileSpriteRepository::TILE_SPLIT);
}

void DrawableBoard::mergeTile(const BoardPosition &pos) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (board.count(pos))
    board.at(pos).loadTile(TileSpriteRepository::TILE_MERGE);
}

void DrawableBoard::currentTile(const BoardPosition &position) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  current_tile.first = position;
  current = true;
}

void DrawableBoard::setDefaultWithCurrent() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  for (auto &it: board) {
    it.second.loadTile(TileSpriteRepository::TILE_DEFAULT);
  }
}

void DrawableBoard::setDefault() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  current = false;
  for (auto &it: board) {
    it.second.loadTile(TileSpriteRepository::TILE_DEFAULT);
  }
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
  if (current) {
    PixelCoordinate pixel(0, 0);
    transformer.position2Pixel(current_tile.first, pixel, width, height);
    current_tile.second.render(pixel.x(), pixel.y());
  }
  for (auto &position: positions) {
    PixelCoordinate pixel(0, 0);
    transformer.position2Pixel(position.first, pixel, width, height);
    position.second.render(pixel.x(), pixel.y());
  }
  for (auto &chessman: chessmen) {
    PixelCoordinate pixel(0, 0);
    transformer.position2Pixel(chessman.first, pixel, width, height);
    chessman.second.render(pixel.x(), pixel.y());
  }
}
