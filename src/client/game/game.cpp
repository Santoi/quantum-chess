#include "game.h"
#include "../sdl/sprite.h"
#include "../sdl/pixel_coordinate.h"
#include <map>
#include <utility>
#include <list>

#define BOARD_MIN_LIMIT .1
#define BOARD_MAX_LIMIT .9

Game::Game(int height, Board &board,
           BlockingQueue<RemoteClientInstruction> &send_queue_):
             scale(height), board(board), send_queue(send_queue_) {}

void Game::loadSprite(Sprite &sprite, int x, int y) {
  const PixelCoordinate pixel(x, y);
  sprites.insert(std::pair<const PixelCoordinate, Sprite>(pixel,
                                                          std::move(sprite)));
}

void Game::setScale(int scale_) {
  scale = scale_;
}

void Game::render() {
  auto &tiles = board.getTiles();
  Sprite &background = board.getBackground();
  auto &chessmen = board.getChessmen();

  for (auto &it : tiles) {
    PixelCoordinate pixel(0, 0);
    transformer.position2Pixel(it.first, pixel, scale);
    it.second.render(pixel.x(), pixel.y());
  }
  background.render(0, 0, scale, scale);
  for (auto &it : chessmen) {
    PixelCoordinate pixel(0, 0);
    transformer.position2Pixel(it.first, pixel, scale);
    it.second.render(pixel.x(), pixel.y());
  }
  for (auto &it : sprites) {
    it.second.render(it.first.x(), it.first.y());
  }
}

bool Game::isPixelInBoard(const PixelCoordinate &pixel) {
  return pixel.x() > scale * BOARD_MIN_LIMIT &&
         pixel.x() < scale * BOARD_MAX_LIMIT &&
         pixel.y() > scale * BOARD_MIN_LIMIT &&
         pixel.y() < scale * BOARD_MAX_LIMIT;
}

void Game::setDefaultBoard() {
  board.setDefault();
}

void Game::moveTiles(const std::list<Position> &positions) {
  for (const Position &position : positions)
    board.moveTile(position);
}

void Game::entangledTiles(const std::list<Position> &positions) {
  for (const Position &position : positions)
    board.entangledTile(position);
}

void Game::quantumTiles(const std::list<Position> &positions) {
  for (const Position &position : positions)
    board.quantumTile(position);
}

void Game::splitTiles(const std::list<Position> &positions) {
  for (const Position &position : positions)
    board.splitTile(position);
}

void Game::mergeTiles(const std::list<Position> &positions) {
  for (const Position &position : positions)
    board.mergeTile(position);
}

void Game::moveChessman(PixelCoordinate &orig, PixelCoordinate &dest) {
  Position orig_, dest_;
  transformer.pixel2Position(orig, orig_, scale);
  transformer.pixel2Position(dest, dest_, scale);
  send_queue.push(std::make_shared<RemoteClientMoveInstruction>(orig_, dest_));
}

void Game::load(std::vector<ChessmanData> & chessman_data_vector) {
  board.load(chessman_data_vector);
}
