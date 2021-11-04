#include "chessman.h"
#include "tower.h"

Tower::Tower(const Position &position, bool white_, Board &board_) : Chessman(position, white_, board_) {}

void Tower::calculatePosibleMoves(const Position & initial, std::vector<Position> & posible_moves) const {
    posible_moves = std::vector<Position>();
    posible_moves.reserve(14);
    std::vector<Position> path;
    // Chequeo en la columna.
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
            if(checkFreePath(path))
                posible_moves.push_back(position);
        }
    }
}