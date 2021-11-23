#include "font.h"
#include "../sdl/renderer.h"

Font::Font(const std::string &font, int ptx, int index): font_(font,
                                                               ptx, index) {}

void Font::renderText(Renderer &renderer, const std::string &text) {
  font_.RenderText_Solid(text, (SDL_Color){255, 255, 255, 255});
}