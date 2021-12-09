#include "text_entry_button.h"
#include "chat/font.h"
#include "chat/drawable_text.h"
#include "drawable_text_entry_button.h"

#define MAX_INPUT 20

TextEntryButton::TextEntryButton(ButtonSpriteRepository &button_repository,
                                 TextSpriteRepository &text_repository,
                                 const std::string &button_name_)
    : text_entry(MAX_INPUT), drawable_text_button(text_repository,
                                                  button_repository,
                                                  button_name_),
      expecting_text_entry(false) {}

void
TextEntryButton::setAreaAndPosition(int x_, int y_, int width, int height) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  drawable_text_button.setAreaAndPosition(x_, y_, width, height);
}

bool TextEntryButton::enableTextEntryIfClicked(const PixelCoordinate &pixel_) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (drawable_text_button.pixelIsOnTextEntry(pixel_)) {
    expecting_text_entry = true;
    text_entry.enableEntry();
    return true;
  }
  return false;
}

void TextEntryButton::disableTextEntry() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  expecting_text_entry = false;
  text_entry.disableEntry();
}

void TextEntryButton::concatIfEnabled(const std::string &text_) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (!expecting_text_entry)
    return;
  if (text_entry.isEnabled())
    text_entry.concat(text_);
}

std::string TextEntryButton::getText() const {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return text_entry.getText();
}

void TextEntryButton::render() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  drawable_text_button.render(text_entry.getText());
}

void TextEntryButton::backspaceIfEnabled() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (!expecting_text_entry)
    return;
  if (text_entry.isEnabled())
    text_entry.backspace();
}
