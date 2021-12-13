#include "drawable_board.h"
#include "../../communication/client_protocol.h"
#include "../../communication/chessman_data.h"
#include "drawable_tile.h"
#include "../renderer.h"
#include <map>
#include <utility>
#include <string>

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
        current_tile(std::make_pair(Position(),
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
    Position row(-1, i);
    Position column(i, -1);
    positions.insert(
            std::pair<const Position, DrawableText>(row, std::move(numbers)));
    positions.insert(
            std::pair<const Position, DrawableText>(column,
                                                    std::move(letters)));
    for (size_t j = 0; j < 8; j++) {
      const Position position(i, j);
      DrawableTile tile(renderer, position.isEven(), tile_repository);
      board.insert(std::pair<const Position, DrawableTile>(position,
                                                           std::move(
                                                                   tile)));
    }
  }
}

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

void DrawableBoard::currentTile(const Position &position) {
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
