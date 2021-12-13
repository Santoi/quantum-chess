#include <vector>
#include <list>
#include <string>
#include <utility>
#include "pawn.h"
#include "../../../common/chess_exception.h"

Pawn::Pawn(const Position &position, bool white_, Board &board_,
           EntanglementLog &entanglement_log_) :
    Chessman(position, white_, board_, entanglement_log_),
    first_move(true) {}

void Pawn::calculateMoves(const Position &initial,
                          std::list<Position> &possible_moves) const {
  possible_moves = std::list<Position>();
  int sum = (white) ? 1 : -1;

  int i = 0, j = 0;
  if ((j = initial.y() + sum) >= 0 && j < 8)
    possible_moves.emplace_back(initial.x(), j);

  if ((i = initial.x() + 1) < 8 && (j = initial.y() + sum) >= 0 && j < 8)
    if (board.getChessmanAt(Position(i, j)))
      possible_moves.emplace_back(i, j);

  if ((i = initial.x() - 1) >= 0 && (j = initial.y() + sum) >= 0 && j < 8)
    if (board.getChessmanAt(Position(i, j)))
      possible_moves.emplace_back(i, j);

  if ((j = initial.y() + sum * 2) >= 0 && j < 8 && first_move)
    possible_moves.emplace_back(initial.x(), j);
}

bool Pawn::move(const Position &initial, const Position &final) {
  bool capture = Chessman::move(initial, final);
  first_move = false;
  return capture;
}

char Pawn::charId() const {
  return 'P';
}

void Pawn::calculatePossibleMerges(const Position &initial,
                                   std::list<Position> &possible_moves) {
  possible_moves = std::list<Position>();
}

void Pawn::calculatePossibleSplits(const Position &initial,
                                   std::list<Position> &possible_moves) {
  possible_moves = std::list<Position>();
}

Chessman::MoveValidationStatus
Pawn::checkIsAValidMove(const Position &initial, const Position &final) {
  Chessman::MoveValidationStatus status =
      Chessman::checkIsAValidMove(initial, final);
  if (status)
    return status;
  if (final.x() == initial.x() && board.getChessmanAt(final) &&
      board.getChessmanAt(final)->isWhite() != white)
    return PAWN_CANT_EAT_LIKE_THAT;
  if (final.x() != initial.x() && board.getChessmanAt(final) &&
      board.getChessmanAt(final)->isWhite() == white)
    return PAWN_CANT_MEASURE_LIKE_THAT;
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



