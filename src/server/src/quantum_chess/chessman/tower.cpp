#include <vector>
#include <string>
#include "chessman.h"
#include "tower.h"

Tower::Tower(const Position &position, bool white_, Board &board_):
             Chessman(position, white_, board_) {}

void Tower::calculateMoves(const Position & initial,
                           std::list<Position> & posible_moves)
                                  const {
    posible_moves = std::list<Position>();
    Position position;
    // Se chequea la columna.
    for (uint8_t i = 0; i < 8; i++) {
        position = Position(initial.x(), i);
        if (position != initial)
            posible_moves.push_back(position);
    }

    // Se chequea la fila.
    for (uint8_t i = 0; i < 8; i++) {
        position = Position(i, initial.y());
        if (position != initial)
            posible_moves.push_back(position);
    }
}

std::string Tower::print() const {
    return "T";
}
