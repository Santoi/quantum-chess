#include "chess_exception.h"
#include <string>

ChessException::ChessException(std::string text_): text(std::move(text_)) {}

const char * ChessException::what() const noexcept {
  return text.c_str();
}
