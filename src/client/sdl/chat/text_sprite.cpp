#include "text_sprite.h"
#include "../sprite.h"
#include "../renderer.h"
#include "font.h"
#include <string>

TextSprite::TextSprite(Renderer &renderer, Font &font_, const std::string &text)
    :
    Sprite(renderer, font_.renderText(text, 'w')), font(font_) {}

void TextSprite::render(const std::string &text, int x, int y, char color) {
  sprite_ = SDL2pp::Texture(renderer.renderer(),
                            font.renderMonoText(text, color));
  renderer.copy(*this, x, y);
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
