#include "text_entry.h"
#include "../renderer.h"

TextEntry::TextEntry(Renderer &renderer_, Font &font_) : renderer(renderer_),
                                                         sprite(renderer_,
                                                                font_,
                                                                " "),
                                                         font(font_),
                                                         string("") {
  SDL_StartTextInput();
}

void TextEntry::add(char c) {
  string.push_back(c);
}

void TextEntry::add(const std::string &text) {
  string += text;
}

void TextEntry::erase() {
  if (not string.empty())
    string.erase(string.end());
}

void TextEntry::render(int x, int y) {
  if (not string.empty())
    sprite.render(string, x, y);
}

TextEntry::~TextEntry() {
  SDL_StopTextInput();
}
