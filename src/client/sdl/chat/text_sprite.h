#ifndef QUANTUM_CHESS_PROJ_TEXT_SPRITE_H
#define QUANTUM_CHESS_PROJ_TEXT_SPRITE_H

//#include "text_entry.h"
#include "../renderer.h"
#include "../sprite.h"
#include "font.h"
#include <SDL2pp/SDL2pp.hh>

class Renderer;
class Font;

class TextSprite: public Sprite {
private:
  SDL2pp::Texture sprite_;
public:
  TextSprite(Renderer &renderer, Font &font, const std::string &text);
  void render();
  SDL2pp::Texture & sprite();

};


#endif //QUANTUM_CHESS_PROJ_TEXT_SPRITE_H
