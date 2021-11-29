#include <vector>
#include <string>
#include "king.h"
#include "tower.h"
#include <algorithm>
#include "../../../../common/src/chess_exception.h"

King::King(const Position &position, bool white_, Board &board_,
           EntanglementLog &entanglement_log_) :
        Chessman(position, white_, board_, entanglement_log_),
        first_move(true), first_line(white ? 0 : 7) {}

void King::calculateMoves(const Position &initial,
                          std::list<Position> &posible_moves)
const {
  posible_moves = std::list<Position>();

  std::vector<int> x_sum = {1, 1, 0, -1, -1, -1, 0, 1};
  std::vector<int> y_sum = {0, 1, 1, 1, 0, -1, -1, -1};

  for (size_t i = 0, j = 0; i < x_sum.size() && j < y_sum.size(); i++, j++) {
    int x = 0, y = 0;
    if ((x = initial.x() + x_sum[i]) < 8 && x >= 0 &&
        (y = initial.y() + y_sum[i]) < 8 && y >= 0) {
      posible_moves.emplace_back(x, y);
    }
  }
  // Only if first move is in king position. A bit hardcoded.
  if (first_move && initial.x() == 4 && initial.y() == first_line) {
    if (checkLongCastling())
      posible_moves.emplace_back(2, first_line);
    if (checkShortCastling())
      posible_moves.emplace_back(6, first_line);
  }
}

void King::calculatePossibleSplits(const Position &initial,
                                   std::list<Position> &posible_moves) {
  // if spliting, dont want to entangle.
  calculateMoves(initial, posible_moves);
  auto it = std::find(posible_moves.begin(), posible_moves.end(),
                      Position(2, first_line));
  if (it != posible_moves.end() && board.getChessmanAt(Position(1, first_line)))
    posible_moves.erase(it);

  for (it = posible_moves.begin(); it != posible_moves.end();) {
    if (checkIsAValidMove(initial, *it)) {
      it = posible_moves.erase(it);
      continue;
    }
    ++it;
  }
}

char King::charId() const {
  return 'K';
}

void King::move(const Position &initial, const Position &final) {
  // See is movement is a castling.
  if (initial == Position(4, first_line) && final == Position(2, first_line)) {
    if (!checkLongCastling())
      throw ChessException("cant to that castling");
    longCastling(positions.begin());
  } else if (initial == Position(4, first_line) &&
             final == Position(6, first_line)) {
    if (!checkShortCastling())
      throw ChessException("cant to that castling");
    shortCastling(positions.begin());
  } else {
    Chessman::move(initial, final);
  }
  first_move = false;
}

void King::split(const Position &initial, const Position &final1,
                 const Position &final2) {
  // Castling
  if (initial == Position(4, first_line)) {
    if (final1 == Position(2, first_line) ||
        final2 == Position(2, first_line)) {
      if (final1 == Position(3, first_line) ||
          final2 == Position(3, first_line))
        throw ChessException("tower is going to occupy that square");
      splitWithCastling(final1, final2);
    } else if (final1 == Position(6, first_line) ||
               final2 == Position(6, first_line)) {
      if (final1 == Position(5, first_line) ||
          final2 == Position(5, first_line))
        throw ChessException("tower is going to occupy that square");
      splitWithCastling(final1, final2);
    } else
      Chessman::split(initial, final1, final2);
  } else {
    Chessman::split(initial, final1, final2);
  }
  first_move = false;
}

void King::splitWithCastling(const Position &final1, const Position &final2) {
  // TODO refactor grande si hay tiempo.
  // It is known that only have one position.
  Position new_real, new_fake;
  bool coin = board.flipACoin();
  new_real = coin ? final1 : final2;
  new_fake = !coin ? final1 : final2;
  // double castle
  if (new_real == Position(2, first_line) &&
      new_fake == Position(6, first_line)) {
    auto it = positions.begin();
    if (!checkLongCastling() || !checkShortCastling())
      throw ChessException("cant to that castling");
    if (board.getChessmanAt(Position(1, first_line)))
      throw ChessException("cant split and entangle at the same time");
    longCastling(it);
    it->setProb(0.5);
    board.addChessmanIn(Position(4, first_line), this);
    positions.emplace_back(4, first_line, 0.5, this);
    shortCastling(++it);
    auto tower_left = (Tower *) board.getChessmanAt(Position(3, first_line));
    auto tower_right = (Tower *) board.getChessmanAt(Position(5, first_line));
    tower_left->entangle(Position(3, first_line), Position(0, first_line),
                         *this,
                         Position(2, first_line));
    board.addChessmanIn(Position(0, first_line), tower_left);
    tower_right->entangle(Position(5, first_line), Position(7, first_line),
                          *this,
                          Position(6, first_line));
    board.addChessmanIn(Position(7, first_line), tower_right);
    return;
  }
  if (new_real == Position(6, first_line) &&
      new_fake == Position(2, first_line)) {
    auto it = positions.begin();
    if (!checkLongCastling() || !checkShortCastling())
      throw ChessException("cant to that castling");
    if (board.getChessmanAt(Position(1, first_line)))
      throw ChessException("cant split and entangle at the same time");
    shortCastling(it);
    it->setProb(0.5);
    board.addChessmanIn(Position(4, first_line), this);
    positions.emplace_back(4, first_line, 0.5, this);
    longCastling(++it);
    auto tower_left = (Tower *) board.getChessmanAt(Position(3, first_line));
    auto tower_right = (Tower *) board.getChessmanAt(Position(5, first_line));
    tower_left->entangle(Position(3, first_line), Position(0, first_line),
                         *this,
                         Position(2, first_line));
    board.addChessmanIn(Position(0, first_line), tower_left);
    tower_right->entangle(Position(5, first_line), Position(7, first_line),
                          *this,
                          Position(6, first_line));
    board.addChessmanIn(Position(7, first_line), tower_right);
    return;
  }
  if (final1 == Position(2, first_line) || final2 == Position(2, first_line)) {
    auto no_castling_pos = (final1 != Position(2, first_line)) ? final1
                                                               : final2;
    auto it = positions.begin();
    if (!checkLongCastling())
      throw ChessException("cant to that castling");
    if (board.getChessmanAt(final1) || board.getChessmanAt(final2))
      throw ChessException("cant split and measure at the same time");
    longCastling(it);
    it->setProb(0.5);
    board.addChessmanIn(no_castling_pos, this);
    if (no_castling_pos == new_real)
      positions.emplace_front(no_castling_pos, 0.5, this);
    else
      positions.emplace_back(no_castling_pos, 0.5, this);
    auto tower_left = (Tower *) board.getChessmanAt(Position(3, first_line));
    tower_left->entangle(Position(3, first_line), Position(0, first_line),
                         *this,
                         Position(2, first_line));
    board.addChessmanIn(Position(0, first_line), tower_left);
    return;
  }
  if (final1 == Position(6, first_line) || final2 == Position(6, first_line)) {
    auto no_castling_pos = (final1 != Position(6, first_line)) ? final1
                                                               : final2;
    auto it = positions.begin();
    if (!checkShortCastling())
      throw ChessException("cant to that castling");
    shortCastling(it);
    it->setProb(0.5);
    board.addChessmanIn(no_castling_pos, this);
    if (no_castling_pos == new_real)
      positions.emplace_front(no_castling_pos, 0.5, this);
    else
      positions.emplace_back(no_castling_pos, 0.5, this);
    auto tower_right = (Tower *) board.getChessmanAt(Position(5, first_line));
    tower_right->entangle(Position(5, first_line), Position(7, first_line),
                          *this,
                          Position(6, first_line));
    board.addChessmanIn(Position(7, first_line), tower_right);
    return;
  }
}

void
King::longCastling(
        const std::_List_iterator<QuantumPosition> &position_to_castle) {
  Tower *tower = (Tower *) board.getChessmanAt(Position(0, first_line));
  // Move tower.
  tower->move(Position(0, first_line), Position(3, first_line));
  if (board.getChessmanAt(Position(1, first_line))) {
    // Using same entangle that move, but, position is changed previously
    // because if tower is in (3, first_line), then king is in (2, first_line)
    position_to_castle->setPosition(Position(2, first_line));
    this->entangle(Position(2, first_line), Position(4, first_line), *tower,
                   Position(3, first_line));
    board.addChessmanIn(Position(2, first_line), this);
  } else {
    position_to_castle->setPosition(Position(2, first_line));
    board.addChessmanOfIn(Position(4, first_line), Position(2, first_line));
  }
}

void King::shortCastling(
        const std::_List_iterator<QuantumPosition> &position_to_castle) {
  Tower *tower = (Tower *) board.getChessmanAt(Position(7, first_line));
  tower->move(Position(7, first_line), Position(5, first_line));
  position_to_castle->setPosition(Position(6, first_line));
  board.addChessmanOfIn(Position(4, first_line), Position(6, first_line));
}

bool King::checkShortCastling() const {
  auto supposed_tower = board.getChessmanAt(Position(7, first_line));
  if (!supposed_tower)
    return false;
  std::pair<Position, Chessman *> chessman_in_path;
  if (board.getChessmanAt(Position(5, first_line)) ||
      board.getChessmanAt(Position(6, first_line)))
    return false;

  if (supposed_tower->charId() == 'T') {
    auto *tower = (Tower *) supposed_tower;
    if (tower->isWhite() == white && tower->notMovedYet())
      return true;
  }
  return false;
}


bool King::checkLongCastling() const {
  auto supposed_tower = board.getChessmanAt(Position(0, first_line));
  if (!supposed_tower)
    return false;
  if (board.getChessmanAt(Position(3, first_line)) ||
      board.getChessmanAt(Position(2, first_line)))
    return false;
  auto next_to_tower = board.getChessmanAt(Position(1, first_line));
  if (next_to_tower && !next_to_tower->isQuantum())
    return false;

  if (supposed_tower->charId() == 'T') {
    auto *tower = (Tower *) supposed_tower;
    if (tower->isWhite() == white && tower->notMovedYet())
      return true;
  }
  return false;
}



