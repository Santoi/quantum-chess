#include "sprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>
#include <string>

Sprite::Sprite(Renderer &renderer, const std::string &file_name, int width,
               int height): renderer(renderer),
               sprite_(renderer.renderer(), file_name),
               width_(width), height_(height) {}

SDL2pp::Texture& Sprite::sprite() {
  return sprite_;
}

void Sprite::render(int x, int y, int width, int height) {
  width_ = width;
  height_ = height;
  renderer.copy(*this, x, y);
}

void Sprite::render(int x, int y) {
  renderer.copy(*this, x, y);
}

void Sprite::loadImage(const std::string &file_name, int width, int height) {
  if (width == 0)
    width = width_;
  if (height == 0)
    height = height_;
  SDL2pp::Texture new_sprite(renderer.renderer(), file_name);
  sprite_ = std::move(new_sprite);
  width_ = width;
  height_ = height;
}

Sprite& Sprite::operator=(Sprite &&other) noexcept {
  renderer = std::move(other.renderer);
  sprite_ = std::move(other.sprite_);
  return *this;
}

int Sprite::width() const {
  return width_;
}

int Sprite::height() const {
  return height_;
}

Sprite::~Sprite() = default;