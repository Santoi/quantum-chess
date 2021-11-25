#ifndef QUANTUM_CHESS_PROJ_TEXT_ENTRY_H
#define QUANTUM_CHESS_PROJ_TEXT_ENTRY_H

#include "../window.h"
#include "font.h"
#include "text_sprite.h"
#include <string>

class TextEntry {
//  Font &font;
  Renderer &renderer;
  TextSprite sprite;
  Font &font;
  std::string string;

public:
  TextEntry(Renderer &renderer_, Font &font_);

  // Add character at the end
  void add(char c);

  // Concatenate string
  void add(const std::string &text);

  // Delete last character
  void erase();

  void render(int x, int y);

  ~TextEntry();
};


#endif //QUANTUM_CHESS_PROJ_TEXT_ENTRY_H
