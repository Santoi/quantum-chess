#include <iostream>
#include "bishop.h"

Bishop::Bishop(const Position &position, bool white_, Board &board_) : Chessman(position, white_, board_) {}

void Bishop::calculatePosibleMoves(const Position &initial, std::vector<Position> &posible_moves) const {
    posible_moves = std::vector<Position>();
    posible_moves.reserve(14);
    std::vector<Position> path;

    // Primero la diagonal hacia la derecha.
    int8_t min = std::min(initial.x(), initial.y());
    for (int8_t i = initial.x() - min, j = initial.y() - min; i < 8 && j < 8; i++, j++) {
        Position position = Position(i, j);
        if (initial != position) {
            calculatePath(initial, position, path);
            if(checkFreePath(path))
                posible_moves.push_back(position);
        }
    }
    // Se recorre para el otro lado
    min = std::min(7 - initial.x(), (int) initial.y());
    for (int8_t i = initial.x() + min, j = initial.y() - min; i >= 0 && j < 8; i--, j++) {
        Position position = Position(i, j);
        if (initial != position) {
            calculatePath(initial, position, path);
            if(checkFreePath(path))
                posible_moves.push_back(position);
        }
    }
}



