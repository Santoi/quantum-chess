#include <sstream>
#include <string>
#include <fstream>
#include "../common/src/chess_exception.h"
#include "ascii_chess.h"

AsciiChess::AsciiChess() : board() {}

void AsciiChess::execute() {
  std::ifstream file("default.txt");
  board.load(file);
  draw();
  while (true) {
    try {
      if (readCommand())
        break;
      draw();
    }
    catch (const ChessException &e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
}

void AsciiChess::draw() {
  for (int8_t i = 7; i >= 0; i--) {
    std::cout << (uint) i << " ";
    for (int8_t j = 0; j < 8; j++) {
      Position position(j, i);
      std::cout << "[";
      if (Chessman *chessman = board.getChessmanAt(position))
        std::cout << *chessman;
      else
        std::cout << " ";
      std::cout << "]";
    }
    std::cout << std::endl;
  }
  std::cout << "   ";
  for (int8_t j = 0; j < 8; j++)
    std::cout << (char) (j + 'A') << "  ";
  std::cout << std::endl;
}

bool AsciiChess::readCommand() {
  std::string color = (board.isNextWhite()) ? "blancas" : "negras";
  std::cout << "Juegan las " << color << " >>  ";

  std::string line;
  std::string op;
  std::getline(std::cin, line);
  std::istringstream iss(line);

  iss >> op;
  if (op == "q" || op == "Q")
    return true;

  if (op == "m" || op == "M") {
    int y1 = 0, y2 = 0;
    char x1 = 0, x2 = 0;
    iss >> x1 >> y1 >> x2 >> y2;
    if (x1 < 'A' || x1 > 'H' || x2 < 'A' || x2 > 'H')
      throw ChessException("posicion invalida");

    board.move(Position((uint8_t) x1 - 'A', (uint8_t) y1),
               Position((uint8_t) x2 - 'A', (uint8_t) y2), false);
  }
  return false;
}


