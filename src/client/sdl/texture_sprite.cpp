#include "texture_sprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>
#include <string>

TextureSprite::TextureSprite(Renderer &renderer, const std::string &file_name,
                             int width,
                             int height) : Sprite(renderer, file_name,
                                                  width, height) {}

void TextureSprite::render(size_t x_src, size_t y_src, size_t x, size_t y,
                           size_t width_src,
                           size_t height_src, size_t width, size_t height) {
  width_ = width;
  height_ = height;
  renderer.copy(*this, x_src, y_src, x, y, width_src, height_src);
}

void TextureSprite::render(size_t x, size_t y, size_t width, size_t height) {
  width_ = width;
  height_ = height;
  renderer.copy(*this, x, y);
}

void TextureSprite::render(size_t x, size_t y) {
  renderer.copy(*this, x, y);
}

void TextureSprite::setBlendMode(int blendMode) {
  sprite_.SetBlendMode(static_cast<SDL_BlendMode>(blendMode));
}

void TextureSprite::setAlpha(float alpha) {
  if (alpha > 1)
    alpha = 1;
  if (alpha < 0)
    alpha = 0;
  sprite_.SetAlphaMod(alpha * 255);
}

int TextureSprite::getImageHeight() const {
  return sprite_.GetHeight();
}

TextureSprite &TextureSprite::operator=(TextureSprite &&other) noexcept {
  renderer = std::move(other.renderer);
  sprite_ = std::move(other.sprite_);
  return *this;
}

TextureSprite::~TextureSprite() = default;
