#include <iostream>
#include "queen.h"

Queen::Queen(const Position &position, bool white_, Board &board_) : Chessman(position, white_, board_) {}

void Queen::calculatePosibleMoves(const Position &initial, std::vector<Position> &posible_moves) const {
    posible_moves = std::vector<Position>();
    posible_moves.reserve(28);
    std::vector<Position> path;

    for (uint8_t i = 0; i < 8; i++) {
        Position position = Position(initial.x(), i);
        if (initial != position) {
            calculatePath(initial, position, path);
            if(checkFreePath(path))
                posible_moves.push_back(position);
        }
    }
    // Chequeo en la fila.
    for (uint8_t i = 0; i < 8; i++) {
        Position position = Position(i, initial.y());
        if (initial != position) {
            calculatePath(initial, position, path);
            if (checkFreePath(path))
                posible_moves.push_back(position);
        }
    }

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

std::string Queen::print() const {
    return "Q";
}



