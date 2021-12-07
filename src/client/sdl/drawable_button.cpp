#include "drawable_button.h"
#include "sprite_repositories/button_sprite_repository.h"

DrawableButton::DrawableButton(ButtonSpriteRepository &button_repository,
                               TextSpriteRepository &text_repository,
                               std::string &&type, std::string &&text)
    : button_repository(button_repository), text_repository(text_repository),
      pressed(&button_repository.getPressed(type)),
      released(&button_repository.getReleased(type)),
      text(text_repository, std::move(text)),
      is_pressed(false), x(0), y(0),
      height(0), width(0) {
}

void DrawableButton::render() {
  if (is_pressed)
    pressed->render(x, y, width, height);
  else
    released->render(x, y, width, height);
  int text_x = x + width / 2 - text.getDrawableWidth() / 2;
  int text_y = y + height / 2 - text.getDrawableHeight() / 2;
  text.render(text_x, text_y);
}

void
DrawableButton::setAreaAndPosition(int x_, int y_, int width_, int height_) {
  x = x_;
  y = y_;
  width = width_;
  height = height_;
}

bool DrawableButton::pixelIsOnButton(const PixelCoordinate &pixel_) {
    is_pressed = (pixel_.x() > (unsigned) (x) && pixel_.x() < (unsigned) (x + width) &&
          pixel_.y() > (unsigned) (y) && pixel_.y() < (unsigned) (y + height));
    return is_pressed;
}

void DrawableButton::setText(std::string &&text_) {
  text.setText(text_);
}

void DrawableButton::disablePressedStatus() {
  is_pressed = false;
}

