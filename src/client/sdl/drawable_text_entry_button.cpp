#include "drawable_text_entry_button.h"

#include <utility>

DrawableTextEntryButton::DrawableTextEntryButton(TextSpriteRepository
                                                 &repository,
                                                 std::string default_text) :
    repository(repository),
    button_name(std::move(default_text)),
    text_box(renderer,
             "img/buttons/White_text_field.png"),
    text(repository, ""),
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
