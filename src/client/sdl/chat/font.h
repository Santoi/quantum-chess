#ifndef QUANTUM_CHESS_PROJ_FONT_H
#define QUANTUM_CHESS_PROJ_FONT_H

#include "../sdl/renderer.h"
#include <SDL2pp/Font.hh>
#include <string>

class Font {
  SDL2pp::Font font_;

public:
  Font(const std::string &font, int ptx, int index = 0);
  void renderText(Renderer &renderer, const std::string &text);

};


#endif //QUANTUM_CHESS_PROJ_FONT_H
