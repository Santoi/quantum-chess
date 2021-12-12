#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_TEXT_ENTRY_BUTTON_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_TEXT_ENTRY_BUTTON_H

#include "../pixel_coordinate.h"
#include "../font.h"
#include "drawable_text.h"
#include "drawable_button.h"
#include <string>

class Renderer;

//TODO public DrawableButton
class DrawableTextEntryButton {
private:
  TextSpriteRepository &text_repository;
  ButtonSpriteRepository &button_repository;
  const std::string button_name;
  DrawableButton text_box;
  DrawableText text;
  bool is_pressed;
  uint32_t x;
  uint32_t y;
  uint32_t width;
  uint32_t height;

public:

  DrawableTextEntryButton() = delete;

  DrawableTextEntryButton(TextSpriteRepository &text_repository,
                          ButtonSpriteRepository &button_repository,
                          std::string default_text);

  void setAreaAndPosition(int x_, int y_, int width_,
                          int height_);

  bool pixelIsOnTextEntry(const PixelCoordinate &pixel);

  void render(const std::string &current_text);

};

#endif //QUANTUM_CHESS_PROJ_DRAWABLE_TEXT_ENTRY_BUTTON_H
