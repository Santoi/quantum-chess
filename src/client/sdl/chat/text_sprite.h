#ifndef QUANTUM_CHESS_PROJ_TEXT_SPRITE_H
#define QUANTUM_CHESS_PROJ_TEXT_SPRITE_H

#include "../sdl/texture_sprite.h"
#include "font.h"
#include "text_entry.h"
#include "../sdl/renderer.h"

class TextSprite: public TextureSprite {
private:
  TextEntry text;
public:
  TextSprite(Renderer &renderer, Font &font);

};


#endif //QUANTUM_CHESS_PROJ_TEXT_SPRITE_H
