#include "font.h"

#define WHITE {255, 255, 255, 255}
#define BLACK {0, 0, 0, 255}

Font::Font(int ptx, int index, char color_) : mono_font("fonts/font-mono.ttf",
                                                        ptx,
                                                        index),
                                              bold_font("fonts/font-bold.ttf",
                                                        ptx, index),
                                              italic_font(
                                                  "fonts/font-italic.ttf", ptx,
                                                  index),

                                              color(BLACK) {
}

SDL2pp::Surface Font::renderText(const std::string &text) {
  return mono_font.RenderText_Solid(text, color);
}

SDL2pp::Surface Font::renderBoldText(const std::string &text) {
  return bold_font.RenderText_Solid(text, color);
}

SDL2pp::Surface Font::renderItalicText(const std::string &text) {
  return italic_font.RenderText_Solid(text, color);
}
