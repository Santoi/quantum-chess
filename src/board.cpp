#include "board.h"
#include <utility>

// TODO crear tablero inicializado
Board::Board(): chessmen(), board() {
    chessmen.reserve(32);
}

void Board::addChessman(Chessman * chessman){
    // TODO debug method.
    // TODO ver de solucionar este tema de los punteros y eso
    // TODO podria hacer algo asi como un wrapper RAII.
    if (!chessman)
        return;
    chessmen.push_back(chessman);
    board.insert(std::pair<Position, Chessman *>(chessman->getPosition(), chessman));
}

void Board::move(const Position & initial, const Position & final) {
    Chessman * chessman = board.at(initial);
    chessman->move(initial, final);
    board.erase(initial);
    board.insert(std::pair<const Position, Chessman *>(final, chessman));
}

Chessman *Board::getChessmanAt(const Position &position) {
    if (board.count(position))
        return board.at(position);
    return nullptr;
}
