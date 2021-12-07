#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_BUTTON_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_BUTTON_H

#include "texture_sprite.h"
#include <vector>
#include "pixel_coordinate.h"
#include "sprite_repositories/button_sprite_repository.h"
#include "sprite_repositories/text_sprite_repository.h"
#include "chat/drawable_text.h"

class Renderer;

class DrawableButton {
private:
  ButtonSpriteRepository &button_repository;
  TextSpriteRepository &text_repository;
  TextureSprite *pressed;
  TextureSprite *released;
  DrawableText text;
  bool is_pressed;
  int x;
  int y;
  int height;
  int width;

public:

  DrawableButton(ButtonSpriteRepository &button_repository,
                 TextSpriteRepository &text_repository,
                 std::string &&type, std::string &&text);

  void setText(std::string &&text_);

  void render();

  bool pixelIsOnButton(const PixelCoordinate &pixel_);

  void disablePressedStatus();

  void setAreaAndPosition(int x_, int y_, int width_, int height_);

  ~DrawableButton() = default;
};

#endif //QUANTUM_CHESS_PROJ_DRAWABLE_BUTTON_H
