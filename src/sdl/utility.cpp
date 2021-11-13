#include "utility.h"
#include <iostream>

void Utility::getTilePosition(const SDL2pp::Renderer &renderer,
                                     Position &position, int x, int y) {
  int total = std::min(renderer.GetOutputHeight(), renderer.GetOutputWidth());
  x *= 10;
  y *= 10;
  x /= total;
  y /= -total;
  x -= 1;
  y += 8;
  Position pos(x, y);
  position = pos;
}
