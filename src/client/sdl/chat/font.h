#ifndef QUANTUM_CHESS_PROJ_FONT_H
#define QUANTUM_CHESS_PROJ_FONT_H

#include <SDL2pp/Font.hh>
#include <string>
#include <map>

class Font {
  SDL2pp::Font mono_font;
  SDL2pp::Font bold_font;
  SDL2pp::Font italic_font;
  SDL_Color color;


public:
  explicit Font(int ptx, int index = 0, char color_ = 'b');

  SDL2pp::Surface renderText(const std::string &text);

  SDL2pp::Surface renderBoldText(const std::string &text);

  SDL2pp::Surface renderItalicText(const std::string &text);

};


#endif //QUANTUM_CHESS_PROJ_FONT_H
