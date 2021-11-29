#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_TEXT_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_TEXT_H

#include "../renderer.h"
#include "text_sprite.h"
#include "font.h"
#include <string>

class DrawableText {
  Renderer &renderer;
  TextSprite sprite;
  Font &font;
  std::string text;
  char color;

public:
  DrawableText(Renderer &renderer_, Font &font_, std::string text = "",
               char color = 'w');

  DrawableText(DrawableText &&other) noexcept;

  DrawableText(const DrawableText &other) = delete;

  size_t length() const;

  int getTextOutputWidth() const;

  int getTextOutputHeight() const;

  void render(int x, int y);

};


#endif //QUANTUM_CHESS_PROJ_DRAWABLE_TEXT_H
