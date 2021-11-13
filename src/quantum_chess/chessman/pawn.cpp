#include <vector>
#include <string>
#include "pawn.h"

Pawn::Pawn(const Position &position, bool white_, Board &board_):
           Chessman(position, white_, board_), first_move(true) {}

void Pawn::calculateMoves(const Position &initial,
                          std::vector<Position> &posible_moves) const {
    posible_moves = std::vector<Position>();
    posible_moves.reserve(4);
    std::vector<Position> path;
    Position position;
    int sum = (white) ? 1 : -1;


    int i = 0, j = 0;
    if ((j = initial.y() + sum) >= 0 && j < 8)
        posible_moves.push_back(Position(initial.x(), j));

    if ((i = initial.x() + 1) < 8 && (j = initial.y() + sum) >= 0 && j < 8)
        if (board.getChessmanAt(Position(i, j)))
            posible_moves.push_back(Position(i, j));

    if ((i = initial.x() - 1) >= 0 && (j = initial.y() + sum) >= 0 && j < 8)
        if (board.getChessmanAt(Position(i, j)))
            posible_moves.push_back(Position(i, j));

    if ((j = initial.y() + sum * 2) >= 0 && j < 8 && first_move)
        posible_moves.push_back(Position(initial.x(), j));
}

void Pawn::move(const Position &initial, const Position &final) {
    Chessman::move(initial, final);
    first_move = false;
}

std::string Pawn::print() const {
    return "P";
}
// TODO validate.
void Pawn::calculatePosibleMerges(const Position &initial,
                                  std::vector<Position> &posible_moves) {
    posible_moves = std::vector<Position> ();
}

void Pawn::calculatePosibleSplits(const Position &initial,
                                  std::vector<Position> &posible_moves) {
    posible_moves = std::vector<Position> ();
}

Chessman::MoveValidationStatus
Pawn::checkIsAValidMove(const Position & initial, const Position & final) {
    Chessman::MoveValidationStatus status =
                                    Chessman::checkIsAValidMove(initial, final);
    if (status)
        return status;
    std::vector<Position> path;
    std::pair<Position, Chessman *> chessman_in_path;
    calculatePath(initial, final, path);
    getMiddlePathChessman(path, chessman_in_path);
    if (chessman_in_path.second)
        return PAWN_CANT_ENTANGLE;
    return OK;
}

Chessman::MoveValidationStatus
Pawn::checkIsAValidMerge(const Position &initial1, const Position &final) {
    return PAWN_CANT_MERGE;
}

Chessman::MoveValidationStatus
Pawn::checkIsAValidSplit(const Position &initial, const Position &final) {
    return PAWN_CANT_SPLIT;
}



