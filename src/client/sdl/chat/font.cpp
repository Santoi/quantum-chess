#include "font.h"

#define BLACK {0x00, 0x00, 0x00}
#define WHITE {0xff, 0xff, 0xff}
#define RED {0xff, 0x00, 0x00}
#define GREEN {0x00, 0x80, 0x00}
#define BLUE {0x00, 0x00, 0xff}
#define GRAY {0x80, 0x80, 0x80}
#define YELLOW {0xff, 0xff, 0x00}
#define NAVY {0x00, 0x00, 0x80}
#define FUCHSIA {0xff, 0x00, 0xff}
#define LIME {0x00, 0xff, 0x00}
#define PURPLE {0x80, 0x00, 0x80}
#define TEAL {0x00, 0xff, 0xff}


Font::Font(int ptx, int index) : regular_font("fonts/font-regular.ttf", ptx,
                                              index),
                                 mono_font("fonts/erusfont.pcf",
                                           ptx,
                                           index),
                                 bold_font("fonts/erusfontbold.pcf",
                                           ptx, index),
                                 italic_font(
                                     "fonts/font-italic.ttf", ptx,
                                     index) {
  colors = {
      {'k', BLACK},
      {'w', WHITE},
      {'r', RED},
      {'g', GREEN},
      {'b', BLUE},
      {'y', YELLOW},
      {'n', NAVY},
      {'f', FUCHSIA},
      {'l', LIME},
      {'p', PURPLE},
      {'d', GRAY},
      {'t', TEAL},
  };
}

SDL2pp::Surface Font::renderText(const std::string &text, char color) {
  return regular_font.RenderText_Solid(text, colors[color]);
}

SDL2pp::Surface Font::renderMonoText(const std::string &text, char color) {
  return mono_font.RenderText_Solid(text, colors[color]);
}

SDL2pp::Surface Font::renderBoldText(const std::string &text, char color) {
  return bold_font.RenderText_Solid(text, colors[color]);
}

SDL2pp::Surface Font::renderItalicText(const std::string &text, char color) {
  return italic_font.RenderText_Solid(text, colors[color]);
}

int Font::size() const {
  return mono_font.GetHeight();
}
