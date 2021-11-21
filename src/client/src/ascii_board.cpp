#include <sstream>
#include <string>
#include "ascii_board.h"

AsciiBoard::AsciiBoard(): board() {}

void AsciiBoard::draw() {
    for (int8_t i = 7; i >= 0; i--) {
        std::cout << (uint) i << " ";
        for (int8_t j = 0; j < 8; j++) {
            Position position(i, j);
            std::cout << "[";
            if (board.count(position)) {
                std::cout << board.at(position);
            }
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

void AsciiBoard::load(std::vector<Position> &positions,
                      std::vector<bool> colors,
                      std::vector<char> &character) {
    board = std::map<Position, AsciiChessman>();
    for (size_t i = 0; i < positions.size(); i++) {
        AsciiChessman chessman(colors[i], character[i]);
        board.insert(std::make_pair(positions[i], chessman));
    }
}
