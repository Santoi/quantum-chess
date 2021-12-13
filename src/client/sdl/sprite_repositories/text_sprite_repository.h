#ifndef QUANTUM_CHESS_PROJ_TEXT_SPRITE_REPOSITORY_H
#define QUANTUM_CHESS_PROJ_TEXT_SPRITE_REPOSITORY_H

#include <map>
#include "../font.h"
#include "../renderer.h"
#include "../sprite.h"
#include <list>

class TextSpriteRepository {
  std::map<char, std::map<char, Sprite>> color_chars;
  Font &font;

  // Load all non-empty ascii character's sprites
  void loadChars(Renderer &renderer, const std::list<char> &colors);

public:
  TextSpriteRepository(Renderer &renderer, Font &font);

  // Get the character sprite in the desired color
  Sprite &getChar(char character, char color);

  size_t getSpriteSize() const;
};


#endif //QUANTUM_CHESS_PROJ_TEXT_SPRITE_REPOSITORY_H
