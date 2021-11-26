#ifndef QUANTUM_CHESS_PROJ_TEXT_H
#define QUANTUM_CHESS_PROJ_TEXT_H

#include "../renderer.h"
#include "text_sprite.h"
#include "font.h"
#include <string>

class Text {
  Renderer &renderer;
  TextSprite sprite;
  Font &font;
  std::string text;

public:
  Text(Renderer &renderer_, Font &font_) : renderer(renderer_),
                                           sprite(renderer_, font_, " "),
                                           font(font_) {}

  void concat(const std::string &str);

  void delete_last();

  void render(int x, int y, int width, int height);

};


#endif //QUANTUM_CHESS_PROJ_TEXT_H
