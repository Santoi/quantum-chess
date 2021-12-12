#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_BUTTON_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_BUTTON_H

#include "../texture_sprite.h"
#include <vector>
#include "../pixel_coordinate.h"
#include "../sprite_repositories/button_sprite_repository.h"
#include "../sprite_repositories/text_sprite_repository.h"
#include "drawable_text.h"

class Renderer;

class DrawableButton {
private:
  ButtonSpriteRepository &button_repository;
  TextSpriteRepository &text_repository;
  TextureSprite *pressed;
  TextureSprite *released;
  DrawableText text;
  bool is_pressed;
  size_t x;
  size_t y;
  size_t height;
  size_t width;

public:

  DrawableButton(ButtonSpriteRepository &button_repository,
                 TextSpriteRepository &text_repository,
                 std::string &&type, std::string &&text);

  void setText(std::string &&text_, char color = 'w');

  void render();

  bool pixelIsOnButton(const PixelCoordinate &pixel_);

  void disablePressedStatus();

  void setAreaAndPosition(size_t x_, size_t y_, size_t width_, size_t height_);

  ~DrawableButton() = default;

  void enablePressedStatus();

  void getAreaAndPosition(size_t &x_, size_t &y_, size_t &width_,
                          size_t &height_);
};

#endif //QUANTUM_CHESS_PROJ_DRAWABLE_BUTTON_H
