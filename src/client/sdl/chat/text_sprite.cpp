#include "text_sprite.h"
#include "../sprite.h"
#include "../renderer.h"
#include <string>

TextSprite::TextSprite(Renderer &renderer, Font &font, const std::string &text):
                       Sprite(renderer),
                       sprite_(renderer.renderer(), font.renderText(text)) {}

void TextSprite::render() {
  renderer.copy(*this, 240, 240);
}

SDL2pp::Texture & TextSprite::sprite() {
  return sprite_;
}
