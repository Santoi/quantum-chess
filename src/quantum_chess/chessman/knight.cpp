#include <vector>
#include <string>
#include "knight.h"

// TODO CAMBIAR POSIBLE MOVES A LIST.

Knight::Knight(const Position &position, bool white_, Board &board_):
               Chessman(position, white_, board_) {}

void Knight::calculateMoves(const Position &initial,
                            std::vector<Position> &posible_moves)
                                   const {
    posible_moves = std::vector<Position>();
    posible_moves.reserve(8);
    std::vector<Position> path;
    Position position;

    std::vector<int> x_sum = {2, 1, -1, -2, -2, -1, 1, 2};
    std::vector<int> y_sum = {1, 2, 2, 1, -1, -2, -2, -1};

    for (size_t i = 0, j = 0; i < x_sum.size() && j < y_sum.size(); i++, j++) {
        int x = 0, y = 0;
        if ((x = initial.x() + x_sum[i]) < 8 && x >= 0 &&
            (y = initial.y() + y_sum[i]) < 8 && y >= 0) {
            posible_moves.push_back(Position(x, y));
        }
    }
}

void Knight::calculatePath(const Position &initial, const Position &final,
                           std::vector<Position> &path) const {
    path = std::vector<Position>();
    path.reserve(1);
    path.push_back(final);
}

std::string Knight::print() const {
    return "H";
}



