#include "game.h"
#include "drawable_board.h"
#include "../sdl/sprite.h"
#include "../sdl/pixel_coordinate.h"
#include "../sdl/window.h"
#include "../../common/src/chess_exception.h"
#include <map>
#include <mutex>
#include <utility>
#include <list>

#define BOARD_H_MIN_LIMIT .1
#define BOARD_H_MAX_LIMIT .9
#define BOARD_W_H_RATIO .4

Game::Game(Window &window,
           BlockingQueue<RemoteClientInstruction> &send_queue_,
           ClientData::Role role_, Font &font) :
        x_scale(window.getWidth()), y_scale(window.getHeight()),
        board(window, "img/stars.jpg", x_scale, y_scale, font),
        send_queue(send_queue_), mutex(), role(role_),
        sound_handler(window.sound_handler()) {}

void Game::setScale(int x_scale_, int y_scale_) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  x_scale = x_scale_;
  y_scale = y_scale_;
}

bool Game::isPixelInBoard(const PixelCoordinate &pixel) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return pixel.x() > x_scale / 2 - y_scale * BOARD_W_H_RATIO &&
         pixel.x() < x_scale / 2 + y_scale * BOARD_W_H_RATIO &&
         pixel.y() > y_scale * BOARD_H_MIN_LIMIT &&
         pixel.y() < y_scale * BOARD_H_MAX_LIMIT;
}

void Game::setDefaultBoard() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  board.setDefault();
}

void Game::setDefaultBoardWithCurrent() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  board.setDefaultWithCurrent();
}

void Game::moveTiles(const std::list<Position> &positions) {
  setDefaultBoardWithCurrent();
  std::lock_guard<std::mutex> lock_guard(mutex);
  for (const Position &position: positions)
    board.moveTile(position);
}

void Game::askMoveTiles(PixelCoordinate &coords) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  Position position;
  transformer.pixel2Position(coords, position, x_scale, y_scale);
  send_queue.push(std::make_shared<RemoteClientPossibleMovesInstruction>(
          std::list<Position>(1, position)));
}

void Game::askSplitTiles(PixelCoordinate &coords) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  Position position;
  transformer.pixel2Position(coords, position, x_scale, y_scale);
  send_queue.push(std::make_shared<RemoteClientPossibleSplitsInstruction>(
          std::list<Position>(1, position)));
}

void Game::askMergeTiles(PixelCoordinate &coords) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  Position position;
  transformer.pixel2Position(coords, position, x_scale, y_scale);
  send_queue.push(std::make_shared<RemoteClientPossibleMergesInstruction>(
          std::list<Position>(1, position)));
}

void Game::askMergeTiles(PixelCoordinate &coords1, PixelCoordinate &coords2) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  Position position1, position2;
  transformer.pixel2Position(coords1, position1, x_scale, y_scale);
  transformer.pixel2Position(coords2, position2, x_scale, y_scale);
  std::list<Position> positions;
  positions.push_back(position1);
  positions.push_back(position2);
  send_queue.push(std::make_shared<RemoteClientPossibleMergesInstruction>(
          std::move(positions)));
}

void
Game::askEntangledTiles(PixelCoordinate &coords) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  Position position;
  transformer.pixel2Position(coords, position, x_scale, y_scale);
  send_queue.push(
          std::make_shared<RemoteClientEntangledChessmanInstruction>(
                  std::list<Position>(1, position)));
}

void
Game::askQuantumTiles(PixelCoordinate &coords) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  Position position;
  transformer.pixel2Position(coords, position, x_scale, y_scale);
  send_queue.push(
          std::make_shared<RemoteClientSameChessmanInstruction>(
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
  setDefaultBoardWithCurrent();
  std::lock_guard<std::mutex> lock_guard(mutex);
  for (const Position &position: positions)
    board.splitTile(position);
}

void Game::mergeTiles(const std::list<Position> &positions) {
  setDefaultBoardWithCurrent();
  std::lock_guard<std::mutex> lock_guard(mutex);
  for (const Position &position: positions)
    board.mergeTile(position);
}

void Game::currentTile(const PixelCoordinate &coordinate) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  Position position;
  transformer.pixel2Position(coordinate, position, x_scale, y_scale);
  PixelCoordinate new_coordinate;
  transformer.position2Pixel(position, new_coordinate, x_scale, y_scale);
  board.currentTile(new_coordinate);
}

void Game::moveChessman(PixelCoordinate &orig, PixelCoordinate &dest) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (role == ClientData::ROLE_SPECTATOR)
    throw ChessException("spectators can't play");
  Position orig_, dest_;
  transformer.pixel2Position(orig, orig_, x_scale, y_scale);
  transformer.pixel2Position(dest, dest_, x_scale, y_scale);
  send_queue.push(std::make_shared<RemoteClientMoveInstruction>(orig_, dest_));
}

void Game::splitChessman(PixelCoordinate &from, PixelCoordinate &to1,
                         PixelCoordinate &to2) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (role == ClientData::ROLE_SPECTATOR)
    throw ChessException("spectators can't play");
  Position from_, to1_, to2_;
  transformer.pixel2Position(from, from_, x_scale, y_scale);
  transformer.pixel2Position(to1, to1_, x_scale, y_scale);
  transformer.pixel2Position(to2, to2_, x_scale, y_scale);
  send_queue.push(
          std::make_shared<RemoteClientSplitInstruction>(from_, to1_, to2_));
}

void Game::mergeChessman(PixelCoordinate &from1, PixelCoordinate &from2,
                         PixelCoordinate &to) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (role == ClientData::ROLE_SPECTATOR)
    throw ChessException("spectators can't play");
  Position from1_, from2_, to_;
  transformer.pixel2Position(from1, from1_, x_scale, y_scale);
  transformer.pixel2Position(from2, from2_, x_scale, y_scale);
  transformer.pixel2Position(to, to_, x_scale, y_scale);
  send_queue.push(
          std::make_shared<RemoteClientMergeInstruction>(from1_, from2_, to_));
}

void Game::load(std::vector<ChessmanData> &chessman_data_vector) {
  setDefaultBoardWithCurrent();
  std::lock_guard<std::mutex> lock_guard(mutex);
  board.load(chessman_data_vector);
}

// Runs in action thread.
void Game::playSplitSound() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  sound_handler.playSplitSound();
}

void Game::playMergeSound() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  sound_handler.playMergeSound();
}

void Game::playCaptureSound() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  sound_handler.playCaptureSound();
}

void Game::toggleSounds() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  sound_handler.toggleSounds();
}

// Todo aca esta bien?
void Game::toggleMusic() {
  sound_handler.toggleMusic();
}

DrawableBoard &Game::getBoard() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return board;
}

ClientData::Role Game::getPlayerRole() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return role;
}
