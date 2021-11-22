#include "client_board.h"
#include "../sdl/renderer.h"
#include "tile.h"
#include "../communication/client_protocol.h"
#include "../communication/chessman_data.h"
#include <map>
#include <utility>
#include <string>

#define BACKGROUND_TRANSPARENCY 0.4

Board::Board(Renderer &renderer_, const std::string &image,
             int width, int height): renderer(renderer_),
             background(renderer_, image, width, height),
             chessman_repository(renderer), tile_repository(renderer) {
  background.setBlendMode(SDL_BLENDMODE_BLEND);
  background.setAlpha(BACKGROUND_TRANSPARENCY);
  for (size_t i = 0; i < 8; i++) {
    for (size_t j = 0; j < 8; j++) {
      const Position position(i, j);
      Tile tile(renderer_, position.isEven(), tile_repository);
      board.insert(std::move(std::pair<const Position, Tile>(position,
                                                             std::move(tile))));
    }
  }
}

// TODO borrar
void Board::render() {
  for (auto & it : board) {
    it.second.render(it.first.x(), it.first.y());
  }
  for (auto & it : chessmen) {
    it.second.render(it.first.x(), it.first.y());
  }
}

void Board::load(std::vector<ChessmanData> & chessman_data_vector) {
  chessmen.clear();
  for (auto & chessman_data: chessman_data_vector) {
    Chessman chessman(renderer, chessman_repository, chessman_data);
    chessmen.insert(std::move(std::pair<const Position, Chessman>
                                (chessman_data.position, std::move(chessman))));
  }
}

void Board::moveChessman(Position &orig, Position &dest) {
  if (chessmen.count(orig) == 0)
    return;
  Chessman &chessman = chessmen.at(orig);
  chessmen.insert(std::move(std::pair<const Position, Chessman>
                            (dest, std::move(chessman))));
  chessmen.erase(orig);
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
  for (auto & it : board) {
    it.second.loadTile(TileSpriteRepository::TILE_DEFAULT);
  }
}

std::map<const Position, Tile>& Board::getTiles() {
  return board;
}

std::map<const Position, Chessman>& Board::getChessmen() {
  return chessmen;
}

Sprite& Board::getBackground() {
  return background;
}
