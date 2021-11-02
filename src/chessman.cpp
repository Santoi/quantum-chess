#include <stdexcept>
#include <vector>
#include "chessman.h"

// TODO implementar comer.

Chessman::Chessman(const Position & position_, bool white_, Board & board_):
                   tree(QuantumPositionTree(position_)),
                   board(board_), white(white_) {}

bool Chessman::canMove(const Position & initial, const Position & final) {
    return checkMiddleChessmen(initial, final, nullptr);
}

void Chessman::move(const Position & initial, const Position & final) {
    std::vector<Chessman *> chessman_in_path;
    if (!checkMiddleChessmen(initial, final, &chessman_in_path))
        throw std::invalid_argument("la ficha no se puede"
                                    " mover a esa posicion");
    tree.move(initial, final);
    // TODO LOGICA DE ENTRELAZAMIENTO, MEASURE ETC.
}

bool Chessman::checkFreeMove(const std::vector<Position> & path,
                             std::vector<Chessman *> * chessmen) {
    if (chessmen)
        chessmen->reserve(MAX_PATH_LENGTH);
    for (auto & position : path) {
        if (Chessman * chessman = board.getChessmanAt(position)) {
            if (!isQuantum() && chessmen)
                return false;
            if (chessmen)
                chessmen->push_back(chessman);
        }
    }
    return true;
}

bool Chessman::isQuantum() const {
    // TODO ver si cuando es tradicional solo tiene una el arbol directamente.
    return tree.leavesSize() != 1;
}

Pawn::Pawn(const Position &position_, bool white_, Board & board_):
           Chessman(position_, white_, board_), first_move(true) {}

bool Pawn::checkMiddleChessmen(const Position &initial, const Position & final,
                               std::vector<Chessman *> * chessmen_in_path) {
    std::vector<Position> path;
    path.reserve(MAX_PATH_LENGTH);
    if (initial.x() != final.x())
        return false;
    if (initial.y() + 2 == final.y() && first_move) {
        path.push_back(Position(initial.y() + 2, initial.x()));
        path.push_back(Position(initial.y() + 1, initial.x()));
    }
    if (initial.y() + 1 == final.y())
        path.push_back(Position(initial.y() + 1, initial.x()));
    if (!path.empty() && checkFreeMove(path, chessmen_in_path)) {
        return true;
    }
    return false;
}

void Pawn::move(const Position &initial, const Position &final) {
    Chessman::move(initial, final);
    first_move = false;
}

