#ifndef QUANTUM_CHESS_PROJ_TEXT_ENTRY_H
#define QUANTUM_CHESS_PROJ_TEXT_ENTRY_H

#include <string>

class TextEntry {
  std::string text;

public:
  TextEntry() = default;

  void enableEntry();

  void disableEntry();

  // Concatenate string
  void concat(const std::string &text_);

  // Delete last character
  void backspace();

  std::string &getText();

  ~TextEntry() = default;
};


#endif //QUANTUM_CHESS_PROJ_TEXT_ENTRY_H
