#include <stdexcept>
#include "chessman.h"

// TODO implementar comer.

Chessman::Chessman(const Position & position_, Board & board_): tree(QuantumPositionTree(position_)), board(board_), quantum(false) {}

void Pawn::move(const Position & initial, const Position & final) {
    std::vector<Chessman *> chessman_in_path;
    if(!canMoveAndCatchMiddleChessmen(initial, final, &chessman_in_path))
        throw std::invalid_argument("la ficha no se puede mover a esa posicion");
    tree.move(initial, final);
    first_move = false;
}

bool Pawn::canMoveAndCatchMiddleChessmen(const Position &initial, const Position & final, std::vector<Chessman *> * chessmen_in_path) {
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
    if (!path.empty() && checkFreeMove(path, chessmen_in_path))
        return true;
    return false;
}

bool Chessman::canMove(const Position & initial, const Position & final) {
    return canMoveAndCatchMiddleChessmen(initial, final, nullptr);
}

bool Chessman::checkFreeMove(const std::vector<Position> & path, std::vector<Chessman *> * chessmen) {
    if(chessmen)
        chessmen->reserve(MAX_PATH_LENGTH);
    for (auto & position : path) {
        if(Chessman * chessman = board.getChessmanAt(position)) {
            if (!chessman->quantum && chessmen)
                return false;
            if (chessmen)
                chessmen->push_back(chessman);
        }
    }
    return true;
}

Pawn::Pawn(const Position &position_, Board & board_) : Chessman(position_, board_), first_move(true) {}
