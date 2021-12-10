#include "renderer.h"
#include "sprite.h"

Sprite::Sprite(Renderer
               &renderer,
               const std::string &file_name,
               size_t width,
               size_t height
) :

    renderer(
        renderer), sprite_(renderer.renderer(), file_name),
    width_(width),
    height_(height) {}

Sprite::Sprite(Renderer
               &renderer,
               const SDL2pp::Surface &surface,
               size_t width,
               size_t height
) :

        renderer(renderer),
        sprite_(renderer.renderer(),
                surface),
        width_(width), height_(height) {}

size_t Sprite::width() const {
  return width_;
}

size_t Sprite::height() const {
  return height_;
}

SDL2pp::Texture &Sprite::sprite() {
  return sprite_;
}

void Sprite::render(size_t x, size_t y) {
  renderer.copy(*this, x, y);
}

void Sprite::render(size_t x, size_t y, size_t width, size_t height) {
  width_ = width;
  height_ = height;
  renderer.copy(*this, x, y);
}
