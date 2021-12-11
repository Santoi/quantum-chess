#ifndef QUANTUM_CHESS_PROJ_TEXT_ENTRY_H
#define QUANTUM_CHESS_PROJ_TEXT_ENTRY_H

#include <string>
#include <mutex>
#include <cstdint>

class TextEntry {
  uint8_t limit;
  std::string text;
  mutable std::mutex mutex;

public:
  explicit TextEntry(uint8_t limit = UINT8_MAX);

  void enableEntry();

  void disableEntry();

  bool isEnabled();

  // Concatenate string if length is less than limit
  bool concat(const std::string &text_);

  // Delete last character
  void backspace();

  void clear();

  std::string getText() const;

  ~TextEntry() = default;
};


#endif //QUANTUM_CHESS_PROJ_TEXT_ENTRY_H
