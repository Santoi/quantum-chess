#include "text_entry.h"
#include "../renderer.h"

TextEntry::TextEntry(Renderer &renderer_, Font &font_) : text(renderer_,
                                                              font_) {
  SDL_StartTextInput();
}

void TextEntry::add(const std::string &str) {
  text.concat(str);
}

void TextEntry::backspace() {
  text.delete_last();
}

void TextEntry::render(int x, int y) {
  text.render(x, y, 100, 10);
}

TextEntry::~TextEntry() {
  SDL_StopTextInput();
}
