#include "board.h"
#include "../sdl/renderer.h"
#include "drawable_tile.h"
#include "../communication/client_protocol.h"
#include "../communication/chessman_data.h"
#include <map>
#include <utility>
#include <string>

#define BACKGROUND_TRANSPARENCY 0.4

Board::Board(Renderer &renderer_, const std::string &image,
             int width, int height) : renderer(renderer_),
                                      background(renderer_, image, width,
                                                 height),
                                      chessman_repository(renderer),
                                      tile_repository(renderer) {
  background.setBlendMode(SDL_BLENDMODE_BLEND);
  background.setAlpha(BACKGROUND_TRANSPARENCY);
  for (size_t i = 0; i < 8; i++) {
    for (size_t j = 0; j < 8; j++) {
      const Position position(i, j);
      DrawableTile tile(renderer_, position.isEven(), tile_repository);
      board.insert(std::move(std::pair<const Position, DrawableTile>(position,
                                                                     std::move(tile))));
    }
  }
}

// TODO borrar
void Board::render() {
  for (auto &it: board) {
    it.second.render(it.first.x(), it.first.y());
  }
  for (auto &it: chessmen) {
    it.second.render(it.first.x(), it.first.y());
  }
}

void Board::load(std::vector<ChessmanData> &chessman_data_vector) {
  chessmen.clear();
  for (auto &chessman_data: chessman_data_vector) {
    DrawableChessman chessman(renderer, chessman_repository, chessman_data);
    chessmen.insert(std::move(std::pair<const Position, DrawableChessman>
                                  (chessman_data.position,
                                   std::move(chessman))));
  }
}

void Board::moveTile(const Position &pos) {
  if (board.count(pos))
    board.at(pos).loadTile(TileSpriteRepository::TILE_MOVE);
}

void Board::quantumTile(const Position &pos) {
  if (board.count(pos))
    board.at(pos).loadTile(TileSpriteRepository::TILE_QUANTUM);
}

void Board::entangledTile(const Position &pos) {
  if (board.count(pos))
    board.at(pos).loadTile(TileSpriteRepository::TILE_ENTANGLED);
}

void Board::splitTile(const Position &pos) {
  if (board.count(pos))
    board.at(pos).loadTile(TileSpriteRepository::TILE_SPLIT);
}

void Board::mergeTile(const Position &pos) {
  if (board.count(pos))
    board.at(pos).loadTile(TileSpriteRepository::TILE_MERGE);
}

void Board::setDefault() {
  for (auto &it: board) {
    it.second.loadTile(TileSpriteRepository::TILE_DEFAULT);
  }
}

std::map<const Position, DrawableTile> &Board::getTiles() {
  return board;
}

std::map<const Position, DrawableChessman> &Board::getChessmen() {
  return chessmen;
}

TextureSprite &Board::getBackground() {
  return background;
}
