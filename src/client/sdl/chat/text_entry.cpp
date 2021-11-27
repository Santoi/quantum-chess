#include "text_entry.h"
#include "../renderer.h"

void TextEntry::concat(const std::string &text_) {
  text.append(text_);
}

void TextEntry::backspace() {
  if (!text.empty())
    text.pop_back();
}

void TextEntry::enableEntry() {
  SDL_StartTextInput();
}

void TextEntry::disableEntry() {
  SDL_StopTextInput();
}

std::string &TextEntry::getText() {
  return text;
}
