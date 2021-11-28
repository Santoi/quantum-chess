#include "texture_sprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>
#include <string>

TextureSprite::TextureSprite(Renderer &renderer, const std::string &file_name,
                             int width,
                             int height) : Sprite(renderer, width, height),
                                           sprite_(renderer.renderer(),
                                                   file_name) {}

SDL2pp::Texture &TextureSprite::sprite() {
  return sprite_;
}

void TextureSprite::render(int x_src, int y_src, int x, int y, int width_src,
                           int height_src, int width, int height) {
  width_ = width;
  height_ = height;
//  renderer.copy(*this, x_src, y_src, x, y, width_src, height_src);
  renderer.copy(*this, x_src, y_src, x, y, width_src, height_src);
}

void TextureSprite::render(int x, int y, int width, int height) {
  width_ = width;
  height_ = height;
  renderer.copy(*this, x, y);
}

void TextureSprite::render(int x, int y) {
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

float TextureSprite::getAlpha() const {
  return sprite_.GetAlphaMod() / 255.0f;
}

int TextureSprite::getImageWidth() const {
  return sprite_.GetWidth();
}

int TextureSprite::getImageHeight() const {
  return sprite_.GetHeight();
}

void
TextureSprite::loadImage(const std::string &file_name, int width, int height) {
  if (width == 0)
    width = width_;
  if (height == 0)
    height = height_;
  SDL2pp::Texture new_sprite(renderer.renderer(), file_name);
  sprite_ = std::move(new_sprite);
  width_ = width;
  height_ = height;
}

TextureSprite &TextureSprite::operator=(TextureSprite &&other) noexcept {
  renderer = std::move(other.renderer);
  sprite_ = std::move(other.sprite_);
  return *this;
}

TextureSprite::~TextureSprite() = default;
