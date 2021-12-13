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

  //Calls drawable_text_button's method that has same name with same
  //parameters.
  void setAreaAndPosition(int x_, int y_, int width, int height);

  //Checks if pixel is on text entry: if it is, expectig_text_entry is set to true
  //and a true is returned. Else a false is returned.
  bool enableTextEntryIfClicked(const PixelCoordinate &pixel);

  //Concats text to text entry if expecting_text_entry is true.
  void concatIfEnabled(const std::string &text_);

  //Backspace text entry if expecting_text_entry is true.
  void backspaceIfEnabled();

  //Returns text entry's current text.
  std::string getText() const;

  //Sets expecting_text_entry to false.
  void disableTextEntry();

  //Calls drawable_text_button's render method.
  void render();
};


#endif //QUANTUM_CHESS_PROJ_TEXT_ENTRY_BUTTON_H
