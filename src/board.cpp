#include "board.h"

// TODO crear tablero inicializado
Board::Board(): chessmen(), board() {}

void Board::move(const Position & initial, const Position & final) {
    Chessman * chessman = board.at(initial);
    chessman->move(initial, final);
    board.erase(initial);
    board.insert(std::pair<const Position, Chessman *>(final, chessman));
}

Chessman *Board::getChessmanAt(const Position &position) {
    Chessman * chessman = nullptr;
    try {
        chessman = board.at(position);
    }
    catch (const std::out_of_range & e){
        return nullptr;
    }
    return chessman;
}
