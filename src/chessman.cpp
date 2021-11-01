#include <stdexcept>
#include "chessman.h"

Chessman::Chessman(const Position & position_): position(position_) {}

void Pawn::move(const Position &new_position) {
    if(!canMove(new_position))
        throw std::invalid_argument("la ficha no se puede mover a esa posicion");
    position = new_position;
    first_move = false;
}

bool Pawn::canMove(const Position &new_position) {
    if (new_position.x() != position.x())
        return false;
    if (position.y() + 2 == new_position.y() && first_move)
        return true;
    if (position.y() + 1 == new_position.y())
        return true;
    return false;
}

Pawn::Pawn(const Position &position_) : Chessman(position_), first_move(true) {}
