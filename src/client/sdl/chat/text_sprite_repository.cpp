#include "text_sprite_repository.h"

TextSpriteRepository::TextSpriteRepository(Renderer
                                           &renderer, Font &font)
        : chars(), font(font) {
  loadChars(renderer);
}

void TextSpriteRepository::loadChars(Renderer &renderer) {
  for (char i = 32; i <= 127 && i >= 32; i++) {
    char s[] = {i, '\0'};
    std::string c(s);
    Sprite character(renderer, font.renderMonoText(c),
                     font.size(), font.size());
    chars.insert(std::make_pair(i, std::move(character)));
  }
}

Sprite &TextSpriteRepository::getChar(char c) {
  return chars.at(c);
}

int TextSpriteRepository::getSpriteSize() const {
  return font.size();
}
