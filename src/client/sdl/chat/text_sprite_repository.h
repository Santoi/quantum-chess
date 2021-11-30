#ifndef QUANTUM_CHESS_PROJ_TEXT_SPRITE_REPOSITORY_H
#define QUANTUM_CHESS_PROJ_TEXT_SPRITE_REPOSITORY_H

#include <map>
#include "font.h"
#include "../renderer.h"
#include "../sprite.h"

class TextSpriteRepository {
  std::map<char, std::map<char, Sprite>> color_chars;
  Font &font;

public:
  TextSpriteRepository(Renderer &renderer, Font &font);

  void loadChars(Renderer &renderer, const std::list<char> &colors);

  Sprite &getChar(char character, char color);

  int getSpriteSize() const;
};


#endif //QUANTUM_CHESS_PROJ_TEXT_SPRITE_REPOSITORY_H
