#ifndef QUANTUM_CHESS_PROJ_TEXT_SPRITE_REPOSITORY_H
#define QUANTUM_CHESS_PROJ_TEXT_SPRITE_REPOSITORY_H

#include <map>
#include "font.h"
#include "../renderer.h"
#include "../sprite.h"

class TextSpriteRepository {
  std::map<char, Sprite> chars;
  Font &font;

public:
  TextSpriteRepository(Renderer &renderer, Font &font);

  void loadChars(Renderer &renderer);

  Sprite &getChar(char c);

  int getSpriteSize() const;
};


#endif //QUANTUM_CHESS_PROJ_TEXT_SPRITE_REPOSITORY_H
