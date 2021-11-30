#include "text_sprite_repository.h"

TextSpriteRepository::TextSpriteRepository(Renderer
                                           &renderer, Font &font)
    : color_chars(), font(font) {
  loadChars(renderer, std::list<char>(font.getColors()));
}

void
TextSpriteRepository::loadChars(Renderer &renderer,
                                const std::list<char> &colors) {
  for (auto color: colors) {
    std::map<char, Sprite> chars;
    color_chars.insert(std::make_pair(color, std::move(chars)));
    for (char i = 32; i <= 127 && i >= 32; i++) {
      char s[] = {i, '\0'};
      std::string c(s);
      Sprite character(renderer, font.renderMonoText(c, color),
                       font.size(), font.size());
      color_chars[color].insert(std::make_pair(i, std::move(character)));
    }
  }
}

Sprite &TextSpriteRepository::getChar(char character, char color) {
  if (!color_chars.count(color))
    color = 'w';
  if (!color_chars[color].count(character))
    character = '?';
  return color_chars.at(color).at(character);
}

int TextSpriteRepository::getSpriteSize() const {
  return font.size();
}
