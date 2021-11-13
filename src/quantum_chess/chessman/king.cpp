#include <vector>
#include <string>
#include "king.h"

King::King(const Position &position, bool white_, Board &board_):
           Chessman(position, white_, board_) {}

void King::calculateMoves(const Position &initial,
                          std::vector<Position> &posible_moves)
                                 const {
    posible_moves = std::vector<Position>();
    posible_moves.reserve(8);
    std::vector<Position> path;

    Position position;

    std::vector<int> x_sum = {1, 1, 0, -1, -1, -1, 0, 1};
    std::vector<int> y_sum = {0, 1, 1, 1, 0, -1, -1, -1};

    for (size_t i = 0, j = 0; i < x_sum.size() && j < y_sum.size(); i++, j++) {
        int x = 0, y = 0;
        if ((x = initial.x() + x_sum[i]) < 8 && x >= 0 &&
                (y = initial.y() + y_sum[i]) < 8 && y >= 0) {
            posible_moves.push_back(Position(x, y));
        }
    }
}

std::string King::print() const {
    return "K";
}



