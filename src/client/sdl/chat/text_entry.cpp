#include "text_entry.h"
#include "../renderer.h"
#include <mutex>
#include <cstdint>

TextEntry::TextEntry(uint8_t limit) : limit(limit) {}

void TextEntry::concat(const std::string &text_) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  text.append(text_);
  if (text.size() >= limit) {
    SDL_StopTextInput();
  }
}

void TextEntry::backspace() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (!text.empty())
    text.pop_back();
}

void TextEntry::clear() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  text.clear();
}

void TextEntry::enableEntry() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  SDL_StartTextInput();
}

void TextEntry::disableEntry() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  SDL_StopTextInput();
}

std::string &TextEntry::getText() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return text;
}