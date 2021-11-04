#include <iostream>
#include "knight.h"

Knight::Knight(const Position &position, bool white_, Board &board_) : Chessman(position, white_, board_) {}

void Knight::calculatePosibleMoves(const Position &initial, std::vector<Position> &posible_moves) const {
    posible_moves = std::vector<Position>();
    posible_moves.reserve(8);
    std::vector<Position> path;
    Position position;

    int i = 0, j = 0;
    if ((i = initial.x() + 2) < 8 && (j = initial.y() + 1) < 8) {
        position = Position(i, j);
        calculatePath(initial, position, path);
        if (checkFreePath(path))
            posible_moves.push_back(position);
    }
    if ((i = initial.x() + 1) < 8 && (j = initial.y() + 2) < 8) {
        position = Position(i, j);
        calculatePath(initial, position, path);
        if (checkFreePath(path))
            posible_moves.push_back(position);
    }
    if ((i = initial.x() - 1) >= 0 && (j = initial.y() + 2) < 8) {
        position = Position(i, j);
        calculatePath(initial, position, path);
        if (checkFreePath(path))
            posible_moves.push_back(position);
    }
    if ((i = initial.x() - 2) >= 0 && (j = initial.y() + 1) < 8) {
        position = Position(i, j);
        calculatePath(initial, position, path);
        if (checkFreePath(path))
            posible_moves.push_back(position);
    }
    if ((i = initial.x() - 2) >= 0 && (j = initial.y() - 1) >= 0) {
        position = Position(i, j);
        calculatePath(initial, position, path);
        if (checkFreePath(path))
            posible_moves.push_back(position);
    }
    if ((i = initial.x() - 1) >= 0 && (j = initial.y() - 2) >= 0) {
        position = Position(i, j);
        calculatePath(initial, position, path);
        if (checkFreePath(path))
            posible_moves.push_back(position);
    }
    if ((i = initial.x() + 1) < 8 && (j = initial.y() - 2) >= 0) {
        position = Position(i, j);
        calculatePath(initial, position, path);
        if (checkFreePath(path))
            posible_moves.push_back(position);
    }
    if ((i = initial.x() + 2) < 8 && (j = initial.y() - 1) >= 0) {
        position = Position(i, j);
        calculatePath(initial, position, path);
        if (checkFreePath(path))
            posible_moves.push_back(position);
    }
}

void Knight::calculatePath(const Position &initial, const Position &final, std::vector<Position> &path) const {
    path = std::vector<Position>();
    path.reserve(1);
    path.push_back(final);
}

std::string Knight::print() const {
    return "H";
}



