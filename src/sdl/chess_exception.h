#ifndef QUANTUM_CHESS_PROJ_CHESS_EXCEPTION_H
#define QUANTUM_CHESS_PROJ_CHESS_EXCEPTION_H

#include <exception>
#include <string>

class ChessException: public std::exception {
private:
  const std::string text;

public:
  explicit ChessException(std::string text_);

  const char * what() const noexcept override;
};


#endif //QUANTUM_CHESS_PROJ_CHESS_EXCEPTION_H
