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
