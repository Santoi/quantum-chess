#include "ascii_chess.h"

void AsciiChess::draw() {
    std::cout << "   ";
    for (int8_t j = 0; j < 8; j++) {
        std::cout << (uint) j << "  ";
    }
    std::cout << std::endl;

    for (int8_t i = 7; i >= 0; i--) {
        std::cout << (uint) i << " ";
        for (int8_t j = 0; j < 8; j++) {
            Position position(j, i);
            std::cout << "[";
            if (Chessman * chessman = board.getChessmanAt(position))
                std::cout << *chessman;
            else
                std::cout << " ";
            std::cout << "]";
        }
        std::cout << std::endl;
    }
}

AsciiChess::AsciiChess(Board &board_): board(board_){}

void AsciiChess::readCommand(std::string first, std::string second, std::string third, std::string forth, std::string fifth) {
    if (first == "m") {
        uint8_t uno = std::strtol(second.c_str(), nullptr, 10);
        uint8_t dos = std::strtol(third.c_str(), nullptr, 10);
        uint8_t tres = std::strtol(forth.c_str(), nullptr, 10);
        uint8_t cuatro = std::strtol(fifth.c_str(), nullptr, 10);
        board.move(Position(uno, dos), Position(tres, cuatro));
    }

}
