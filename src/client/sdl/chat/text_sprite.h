#ifndef QUANTUM_CHESS_PROJ_TEXT_SPRITE_H
#define QUANTUM_CHESS_PROJ_TEXT_SPRITE_H

#include "../renderer.h"
#include "../sprite.h"
#include "font.h"
#include <SDL2pp/SDL2pp.hh>
#include <string>

class Renderer;

class Font;

class TextSprite : public Sprite {
private:
  SDL2pp::Texture sprite_;
  Font &font;

public:
  TextSprite(Renderer &renderer, Font &font_, const std::string &text);

  void render(const std::string &text, int x, int y);

  void render(const std::string &text, int x, int y, int width, int height);

  SDL2pp::Texture &sprite();

};


#endif //QUANTUM_CHESS_PROJ_TEXT_SPRITE_H
