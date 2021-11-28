#include "renderer.h"
#include "sprite.h"

Sprite::Sprite(Renderer &renderer_, int width, int height) : renderer(
    renderer_), width_(width), height_(height) {}

int Sprite::width() const {
  return width_;
}

int Sprite::height() const {
  return height_;
}
