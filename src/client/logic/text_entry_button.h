#ifndef QUANTUM_CHESS_PROJ_TEXT_ENTRY_BUTTON_H
#define QUANTUM_CHESS_PROJ_TEXT_ENTRY_BUTTON_H

#include "../sdl/pixel_coordinate.h"
#include "text_entry.h"
#include "../sdl/drawables/drawable_text_entry_button.h"
#include <string>
#include <mutex>

class TextEntryButton {
private:
  TextEntry text_entry;
  DrawableTextEntryButton drawable_text_button;
  mutable std::mutex mutex;
  bool expecting_text_entry;

public:

  TextEntryButton() = delete;

  TextEntryButton(ButtonSpriteRepository &button_repository,
                  TextSpriteRepository &text_repository,
                  const std::string &button_name_);

  void setAreaAndPosition(int x_, int y_, int width, int height);

  bool enableTextEntryIfClicked(const PixelCoordinate &pixel);

  void concatIfEnabled(const std::string &text_);

  void backspaceIfEnabled();

  std::string getText() const;

  void disableTextEntry();

  void render();

private:
  bool pixelIsOnTextEntry(const PixelCoordinate &pixel);
};


#endif //QUANTUM_CHESS_PROJ_TEXT_ENTRY_BUTTON_H
