#include "scene.h"
#include "sprite.h"
#include "pixel_coordinate.h"
#include <map>

Scene::Scene(int height, Board &board): scale(height), board(board) {}

void Scene::loadSprite(Sprite &sprite, int x, int y) {
  const PixelCoordinate pixel(x, y);
  sprites.insert(std::pair<const PixelCoordinate, Sprite>(pixel, std::move(sprite)));
}

void Scene::setScale(int scale_) {
  scale = scale_;
}

void Scene::render() {
  auto &tiles = board.getTiles();
  auto &chessmen = board.getChessmen();

  for (auto &it : sprites) {
    it.second.render(it.first.x(), it.first.y());
  }
  for (auto &it : tiles) {
    PixelCoordinate pixel(0, 0);
    transformer.position2Pixel(it.first, pixel, scale);
    it.second.render(pixel.x(), pixel.y());
  }
  for (auto &it : chessmen) {
    PixelCoordinate pixel(0, 0);
    transformer.position2Pixel(it.first, pixel, scale);
    it.second.render(pixel.x(), pixel.y());
  }
}

void Scene::setDefaultBoard() {
  board.setDefault();
}

void Scene::moveTiles(const std::list<Position> &positions) {
  for (const Position &position : positions)
    board.moveTile(position);
}

void Scene::entangledTiles(const std::list<Position> &positions) {
  for (const Position &position : positions)
    board.entangledTile(position);
}

void Scene::quantumTiles(const std::list<Position> &positions) {
  for (const Position &position : positions)
    board.quantumTile(position);
}

void Scene::splitTiles(const std::list<Position> &positions) {
  for (const Position &position : positions)
    board.splitTile(position);
}

void Scene::mergeTiles(const std::list<Position> &positions) {
  for (const Position &position : positions)
    board.mergeTile(position);
}

void Scene::moveChessman(PixelCoordinate &orig, PixelCoordinate &dest) {
  Position orig_, dest_;
  transformer.pixel2Position(orig, orig_, scale);
  transformer.pixel2Position(dest, dest_, scale);
  board.moveChessman(orig_, dest_);
}
