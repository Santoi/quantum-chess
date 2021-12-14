#ifndef QUANTUM_CHESS_PROJ_FONT_H
#define QUANTUM_CHESS_PROJ_FONT_H

#include <SDL2pp/Font.hh>
#include <SDL2pp/SDLTTF.hh>
#include <string>
#include <map>
#include <list>

class Font {
  SDL2pp::SDLTTF ttf;
  SDL2pp::Font mono_font;
  std::map<char, SDL_Color> colors;

public:
  explicit Font(int ptx, int index = 0);

  SDL2pp::Surface renderMonoText(const std::string &text, char color = 'w');

  size_t size() const;

  std::list<char> getColors() const;
};


#endif //QUANTUM_CHESS_PROJ_FONT_H
