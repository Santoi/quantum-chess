#include <iostream>
#include "pawn.h"

Pawn::Pawn(const Position &position, bool white_, Board &board_) : Chessman(position, white_, board_), first_move(true) {}

void Pawn::calculatePosibleMoves(const Position &initial, std::vector<Position> &posible_moves) const {
    posible_moves = std::vector<Position>();
    posible_moves.reserve(4);
    std::vector<Position> path;
    Position position;
    int sum = (white) ? 1 : -1;


    int i = 0, j = 0;
    if ((j = initial.y() + sum) >= 0 && j < 8) {
        position = Position(initial.x(), j);
        calculatePath(initial, position, path);
        if (checkFreePath(path))
            posible_moves.push_back(position);
    }
    if ((i = initial.x() + 1) < 8 && (j = initial.y() + sum) >= 0 && j < 8) {
        position = Position(i, j);
        // Si hay algo en la casilla, se agrega
        if (board.getChessmanAt(position)) {
            calculatePath(initial, position, path);
            if (checkFreePath(path))
                posible_moves.push_back(position);
        }
    }
    if ((i = initial.x() - 1) >= 0 && (j = initial.y() + sum) >= 0 && j < 8) {
        position = Position(i, j);
        // Si hay algo en la casilla, se agrega.
        if (board.getChessmanAt(position)) {
            calculatePath(initial, position, path);
            if (checkFreePath(path))
                posible_moves.push_back(position);
        }
    }
    if ((j = initial.y() + sum * 2) >= 0 && j < 8 && first_move) {
        position = Position(initial.x(), j);
        calculatePath(initial, position, path);
        if (checkFreePath(path))
            posible_moves.push_back(position);
    }
}

void Pawn::move(const Position &initial, const Position &final) {
    Chessman::move(initial, final);
    first_move = false;
}

std::string Pawn::print() const {
    return "P";
}



