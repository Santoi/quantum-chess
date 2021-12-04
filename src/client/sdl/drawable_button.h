#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_BUTTON_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_BUTTON_H

#include "texture_sprite.h"
#include <vector>
#include "pixel_coordinate.h"
#include "sprite_repositories/button_sprite_repository.h"

class Renderer;

class DrawableButton {
private:
  Renderer &renderer;
  std::vector<TextureSprite> sprites;
  int scale;
  bool is_pressed;
  int x;
  int y;
  int height;
  int width;

public:

  explicit DrawableButton(ButtonSpriteRepository &repository);

  void setScale(const int &scale_);

  void render();

  bool pixelIsOnButton(const PixelCoordinate &pixel_);

  void setAreaAndPosition(int x, int y, int height, int width);

  ~DrawableButton() = default;
};

#endif //QUANTUM_CHESS_PROJ_DRAWABLE_BUTTON_H
