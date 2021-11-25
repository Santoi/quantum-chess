#include "game.h"
#include "../sdl/sprite.h"
#include "../sdl/pixel_coordinate.h"
#include "../sdl/window.h"
#include "chess_exception.h"
#include <map>
#include <mutex>
#include <utility>
#include <list>

#define BOARD_MIN_LIMIT .1
#define BOARD_MAX_LIMIT .9

Game::Game(Window &window,
           BlockingQueue<RemoteClientInstruction> &send_queue_,
           ClientData::Role role_) :
        scale(window.renderer().getMinDimension()),
        board(window.renderer(), "img/stars.jpg", scale, scale),
        send_queue(send_queue_), mutex(), role(role_) {}

void Game::loadSprite(Sprite &sprite, int x, int y) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  const PixelCoordinate pixel(x, y);
  sprites.insert(std::pair<const PixelCoordinate, Sprite>(pixel,
                                                          std::move(sprite)));
}

void Game::setScale(int scale_) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  scale = scale_;
}

void Game::render() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  auto &tiles = board.getTiles();
  Sprite &background = board.getBackground();
  auto &chessmen = board.getChessmen();

  for (auto &it: tiles) {
    PixelCoordinate pixel(0, 0);
    transformer.position2Pixel(it.first, pixel, scale);
    it.second.render(pixel.x(), pixel.y());
  }
  background.render(0, 0, scale, scale);
  for (auto &it: chessmen) {
    PixelCoordinate pixel(0, 0);
    transformer.position2Pixel(it.first, pixel, scale);
    it.second.render(pixel.x(), pixel.y());
  }
  for (auto &it: sprites) {
    it.second.render(it.first.x(), it.first.y());
  }
}

bool Game::isPixelInBoard(const PixelCoordinate &pixel) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return pixel.x() > scale * BOARD_MIN_LIMIT &&
         pixel.x() < scale * BOARD_MAX_LIMIT &&
         pixel.y() > scale * BOARD_MIN_LIMIT &&
         pixel.y() < scale * BOARD_MAX_LIMIT;
}

void Game::setDefaultBoard() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  board.setDefault();
}

// TODO poner esta logica aca o ahcer que lo haga el event handler?
void Game::moveTiles(const std::list<Position> &positions) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  for (const Position &position: positions)
    board.moveTile(position);
}

void Game::askMoveTiles(PixelCoordinate &coords) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  Position position;
  transformer.pixel2Position(coords, position, scale);
  send_queue.push(std::make_shared<RemoteClientPossibleMovesInstruction>(
          std::list<Position>(1, position)));
}

void Game::askSplitTiles(PixelCoordinate &coords) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  Position position;
  transformer.pixel2Position(coords, position, scale);
  send_queue.push(std::make_shared<RemoteClientPossibleSplitsInstruction>(
          std::list<Position>(1, position)));
}

void Game::entangledTiles(const std::list<Position> &positions) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  for (const Position &position: positions)
    board.entangledTile(position);
}

void Game::quantumTiles(const std::list<Position> &positions) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  for (const Position &position: positions)
    board.quantumTile(position);
}

void Game::splitTiles(const std::list<Position> &positions) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  for (const Position &position: positions)
    board.splitTile(position);
}

void Game::mergeTiles(const std::list<Position> &positions) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  for (const Position &position: positions)
    board.mergeTile(position);
}

void Game::moveChessman(PixelCoordinate &orig, PixelCoordinate &dest) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (role == ClientData::ROLE_SPECTATOR)
    throw ChessException("you cannot move being spectator");
  Position orig_, dest_;
  transformer.pixel2Position(orig, orig_, scale);
  transformer.pixel2Position(dest, dest_, scale);
  send_queue.push(std::make_shared<RemoteClientMoveInstruction>(orig_, dest_));
}

void Game::splitChessman(PixelCoordinate &from, PixelCoordinate &to1,
                         PixelCoordinate &to2) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (role == ClientData::ROLE_SPECTATOR)
    throw ChessException("you cannot move being spectator");
  Position from_, to1_, to2_;
  transformer.pixel2Position(from, from_, scale);
  transformer.pixel2Position(to1, to1_, scale);
  transformer.pixel2Position(to2, to2_, scale);
  send_queue.push(
          std::make_shared<RemoteClientSplitInstruction>(from_, to1_, to2_));
}

void Game::load(std::vector<ChessmanData> &chessman_data_vector) {
  setDefaultBoard();
  std::lock_guard<std::mutex> lock_guard(mutex);
  board.load(chessman_data_vector);
}

