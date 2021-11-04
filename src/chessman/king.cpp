#include <iostream>
#include "king.h"

King::King(const Position &position, bool white_, Board &board_) : Chessman(position, white_, board_) {}

void King::calculatePosibleMoves(const Position &initial, std::vector<Position> &posible_moves) const {
    posible_moves = std::vector<Position>();
    posible_moves.reserve(8);
    std::vector<Position> path;

    // TODO Implmenetar

    Position position;

    int i = 0, j = 0;
    if ((i = initial.x() + 1) < 8) {
        position = Position(i, initial.y());
        calculatePath(initial, position, path);
        if (checkFreePath(path))
            posible_moves.push_back(position);
    }
    if ((i = initial.x() + 1) < 8 && (j = initial.y() + 1) < 8) {
        position = Position(i, j);
        calculatePath(initial, position, path);
        if (checkFreePath(path))
            posible_moves.push_back(position);
    }
    if ((j = initial.y() + 1) < 8) {
        position = Position(initial.x(), j);
        calculatePath(initial, position, path);
        if (checkFreePath(path))
            posible_moves.push_back(position);
    }
    if ((i = initial.x() - 1) >= 0 && (j = initial.y() + 1) < 8) {
        position = Position(i, j);
        calculatePath(initial, position, path);
        if (checkFreePath(path))
            posible_moves.push_back(position);
    }
    if ((i = initial.x() - 1) >= 0) {
        position = Position(i, initial.y());
        calculatePath(initial, position, path);
        if (checkFreePath(path))
            posible_moves.push_back(position);
    }
    if ((i = initial.x() - 1) >= 0 && (j = initial.y() - 1) >= 0) {
        position = Position(i, j);
        calculatePath(initial, position, path);
        if (checkFreePath(path))
            posible_moves.push_back(position);
    }
    if ((j = initial.y() - 1) >= 0) {
        position = Position(initial.x(), j);
        calculatePath(initial, position, path);
        if (checkFreePath(path))
            posible_moves.push_back(position);
    }
    if ((i = initial.x() + 1) < 8 && (j = initial.y() - 1) >= 0) {
        position = Position(i, j);
        calculatePath(initial, position, path);
        if (checkFreePath(path))
            posible_moves.push_back(position);
    }


}

std::string King::print() const {
    return "K";
}



