#include <vector>
#include <string>
#include "chessman.h"
#include "tower.h"

Tower::Tower(const Position &position, bool white_, Board &board_):
             Chessman(position, white_, board_) {}

void Tower::calculateMoves(const Position & initial,
                           std::vector<Position> & posible_moves)
                                  const {
    posible_moves = std::vector<Position>();
    posible_moves.reserve(14);
    // Se chequea la columna.
    for (uint8_t i = 0; i < 8; i++)
        posible_moves.push_back(Position(initial.x(), i));

    // Se chequea la fila.
    for (uint8_t i = 0; i < 8; i++)
        posible_moves.push_back(Position(i, initial.y()));
}

std::string Tower::print() const {
    return "T";
}
