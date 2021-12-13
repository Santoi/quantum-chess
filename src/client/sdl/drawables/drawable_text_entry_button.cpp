#include "drawable_text_entry_button.h"

#include <utility>

DrawableTextEntryButton::DrawableTextEntryButton(
    TextSpriteRepository &text_repository,
    ButtonSpriteRepository &button_repository,
    std::string default_text) :
    text_repository(text_repository),
    button_repository(button_repository),
    button_name(std::move(default_text)),
    text_box(button_repository, text_repository, "text", ""),
    text(text_repository, ""), is_pressed(false),
    x(0), y(0), width(0),
    height(0) {}

void DrawableTextEntryButton::setAreaAndPosition(int x_, int y_, int width_,
                                                 int height_) {
  x = x_;
  y = y_;
  width = width_;
  height = height_;
}

bool DrawableTextEntryButton::isPixelOnTextEntry(
    const PixelCoordinate &pixel) {
  is_pressed = (pixel.x() > x && pixel.x() < x + width &&
                pixel.y() > y && pixel.y() < y + height);
  return is_pressed;
}

void DrawableTextEntryButton::render(const std::string &current_text) {
  is_pressed ? text_box.enablePressedStatus() : text_box.disablePressedStatus();
  text_box.setAreaAndPosition(x, y, width, height);
  text_box.render();
  if (current_text.empty()) {
    text.setColor('d');
    text.setText(button_name);
  } else {
    text.setColor('w');
    text.setText(current_text);
  }
  int text_x = x + width / 2 - text.getDrawableWidth() / 2;
  int text_y = y + height / 2 - text.getDrawableHeight() / 2;
  text.render(text_x, text_y);
}
