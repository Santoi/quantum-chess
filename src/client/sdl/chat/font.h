#ifndef QUANTUM_CHESS_PROJ_FONT_H
#define QUANTUM_CHESS_PROJ_FONT_H

#include <SDL2pp/Font.hh>
#include <SDL2pp/SDLTTF.hh>
#include <string>
#include <map>

class Font {
  SDL2pp::SDLTTF ttf;
  SDL2pp::Font regular_font;
  SDL2pp::Font mono_font;
  SDL2pp::Font bold_font;
  SDL2pp::Font italic_font;
  std::map<char, SDL_Color> colors;

public:
  explicit Font(int ptx, int index = 0);

  SDL2pp::Surface renderText(const std::string &text, char color = 'w');

  SDL2pp::Surface renderMonoText(const std::string &text, char color = 'w');

  SDL2pp::Surface renderBoldText(const std::string &text, char color = 'w');

  SDL2pp::Surface renderItalicText(const std::string &text, char color = 'w');

  int size() const;
};


#endif //QUANTUM_CHESS_PROJ_FONT_H
