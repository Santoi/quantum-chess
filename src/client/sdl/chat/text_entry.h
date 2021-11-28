#ifndef QUANTUM_CHESS_PROJ_TEXT_ENTRY_H
#define QUANTUM_CHESS_PROJ_TEXT_ENTRY_H

#include <string>
#include <mutex>

class TextEntry {
  std::string text;
  std::mutex mutex;

public:
  TextEntry() = default;

  void enableEntry();

  void disableEntry();

  // Concatenate string
  void concat(const std::string &text_);

  // Delete last character
  void backspace();

  void clear();

  std::string &getText();

  ~TextEntry() = default;
};


#endif //QUANTUM_CHESS_PROJ_TEXT_ENTRY_H
