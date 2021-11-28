#include "text_sprite.h"
#include "../sprite.h"
#include "../renderer.h"
#include "font.h"
#include <string>

TextSprite::TextSprite(Renderer &renderer, Font &font_, const std::string &text)
    :
    Sprite(renderer),
    sprite_(renderer.renderer(), font_.renderText(text, 'b')), font(font_) {}

void TextSprite::render(const std::string &text, int x, int y, char color) {
  sprite_ = SDL2pp::Texture(renderer.renderer(),
                            font.renderMonoText(text, color));
  renderer.copy(*this, x, y);
}

SDL2pp::Texture &TextSprite::sprite() {
  return sprite_;
}

void
TextSprite::render(const std::string &text, int x, int y, int width, int height,
                   char color) {
  sprite_ = SDL2pp::Texture(renderer.renderer(),
                            font.renderMonoText(text, color));
  width_ = width;
  height_ = height;
  renderer.copy(*this, x, y);
}
