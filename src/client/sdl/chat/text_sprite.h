#ifndef QUANTUM_CHESS_PROJ_TEXT_SPRITE_H
#define QUANTUM_CHESS_PROJ_TEXT_SPRITE_H

#include "../sprite.h"
#include "../renderer.h"
#include "font.h"
#include <SDL2pp/SDL2pp.hh>
#include <string>

class Renderer;

class Font;

class TextSprite : public Sprite {
private:
  Font &font;

public:
  TextSprite(Renderer &renderer, Font &font_, const std::string &text);

  void render(const std::string &text, int x, int y, char color);

  void render(const std::string &text, int x, int y, int width, int height,
              char color);
};


#endif //QUANTUM_CHESS_PROJ_TEXT_SPRITE_H
