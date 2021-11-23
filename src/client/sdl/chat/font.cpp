#include "font.h"
#include "../renderer.h"

#define WHITE {255, 255, 255, 255}
#define BLACK {0, 0, 0, 255}

Font::Font(const std::string &font, int ptx, int index): font_(font,
                                                               ptx,
                                                               index),
                                                         color(WHITE) {}

SDL2pp::Surface Font::renderText(const std::string &text) {
  return font_.RenderText_Solid(text, color);
}