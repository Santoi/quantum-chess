#include "drawable_text_entry_button.h"

#include <utility>

DrawableTextEntryButton::DrawableTextEntryButton(
    TextSpriteRepository &text_repository,
    ButtonSpriteRepository &button_repository,
    std::string default_text) :
    text_repository(text_repository),
    button_repository(button_repository),
    button_name(std::move(default_text)),
    text_box(button_repository),
    text(text_repository, ""),
    x(0), y(0), width(0),
    height(0) {}

void DrawableTextEntryButton::setAreaAndPosition(int x_, int y_,
                                                 int height_, int width_) {
  x = x_;
  y = y_;
  height = height_;
  width = width_;
}

bool DrawableTextEntryButton::pixelIsOnTextEntry(
    const PixelCoordinate &pixel) const {
  return pixel.x() > x && pixel.x() < x + width &&
         pixel.y() > y && pixel.y() < y + height;
}

void DrawableTextEntryButton::render(const std::string &current_text) {
  text_box.render(x + 60, y, width - 60, height);
  if (current_text.empty()) {
    text.setColor('d');
    text.setText(button_name);
  } else {
    text.setText(current_text);
  }
  text.render(x, y);
}
