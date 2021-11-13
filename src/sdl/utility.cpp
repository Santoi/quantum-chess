#include "utility.h"
#include <iostream>

bool Utility::getTilePosition(const SDL2pp::Renderer &renderer,
                                     Position &position, int x, int y) {
  int total = std::min(renderer.GetOutputHeight(), renderer.GetOutputWidth());
  x *= 10;
  y *= 10;
  x /= total;
  y /= -total;
  x -= 1;
  y += 8;
  if (x > 7 or y > 7)
    return false;
  Position pos(x, y);
  position = pos;
  return true;
}
