#ifndef QUANTUM_CHESS_PROJ_TEXT_ENTRY_H
#define QUANTUM_CHESS_PROJ_TEXT_ENTRY_H

#include "../renderer.h"
#include "font.h"
#include "text_sprite.h"
#include "text.h"
#include <string>

class TextEntry {
  Text text;

public:
  TextEntry(Renderer &renderer_, Font &font_);

  // Concatenate string
  void add(const std::string &text);

  // Delete last character
  void backspace();

  void render(int x, int y);

  ~TextEntry();
};


#endif //QUANTUM_CHESS_PROJ_TEXT_ENTRY_H
