#include <stdexcept>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <iostream>
#include "chessman.h"
#include "../../../common/chess_exception.h"

Chessman::Chessman(const Position &position_, bool white_, Board &board_,
                   EntanglementLog &entanglement_log_) :
        positions(1, QuantumPosition(position_, 1, this)),
        board(board_), white(white_), entanglement_log(entanglement_log_) {}


bool Chessman::move(const Position &initial, const Position &final) {
  bool capture = false;
  // Check if can be moved.
  std::vector<Position> path;
  std::list<Position> posible_moves;
  calculateMoves(initial, posible_moves);
  auto final_it = std::find(posible_moves.begin(), posible_moves.end(),
                            final);
  if (final_it == posible_moves.end())
    throw ChessException("that chessman_ cant do that move");
  moveValidationExceptionThrower(checkIsAValidMove(initial, final));

  // Search path and get middle path chessman_.
  std::pair<Position, Chessman *> chessman_in_path;
  calculatePath(initial, final, path);
  getMiddlePathChessman(path, chessman_in_path);

  Chessman *final_chessman = board.getChessmanAt(final);

  /* If initial is quantic and there is a chessman_ at the end, or there is a
   * chessman_ at the end and this is quantic, then measure both chessmen. */
  if ((this->isQuantum() && final_chessman) ||
      (final_chessman && final_chessman->isQuantum())) {
    this->measure(initial);
    final_chessman->measure(final);
    if (positions.front() != initial ||
        (final_chessman->getPosition() == final
         && final_chessman->white == white))
      return false;
  }
  // Measure solved from here, final_chessman is loaded again.
  // If there is final chessman_, then is removed of the board.
  final_chessman = board.getChessmanAt(final);
  if (final_chessman) {
    if (final_chessman->charId() == 'K') {
      std::string color = white ? "white" : "black";
      board.pushToLog("End of the game, " + color + " wins");
      board.endGame();
    }
    board.removeChessmanOf(final);
    capture = true;
    board.pushToLog(final.print() + " was captured");
  }

  // If there is a chessman_ in path then entangle.
  if (chessman_in_path.second) {
    entangle(initial, final, *chessman_in_path.second,
             chessman_in_path.first);
    board.addChessmanIn(final, this);
  } else {
    auto initial_qp_it = std::find(positions.begin(),
                                   positions.end(), initial);
    initial_qp_it->setPosition(final);
    board.addChessmanOfIn(initial, final);
  }
  board.pushToLog(initial.print() + " moved to " + final.print());
  return capture;
}

void Chessman::split(const Position &initial, const Position &final1,
                     const Position &final2) {
  std::list<Position> posible_moves;
  calculateMoves(initial, posible_moves);
  auto final_it = std::find(posible_moves.begin(), posible_moves.end(),
                            final1);
  if (final_it == posible_moves.end())
    throw ChessException("that chessman_ cant do that split");
  moveValidationExceptionThrower(checkIsAValidSplit(initial, final1));
  final_it = std::find(posible_moves.begin(), posible_moves.end(),
                       final2);
  if (final_it == posible_moves.end())
    throw ChessException("that chessman_ cant do that split");
  moveValidationExceptionThrower(checkIsAValidSplit(initial, final2));

  if (final1 == final2)
    throw ChessException("cannot split into the same square");

  // Even if not real, the coin is flipped.
  Position new_real, new_fake;
  bool coin = board.flipACoin();
  new_real = coin ? final1 : final2;
  new_fake = !coin ? final1 : final2;

  auto initial_qp_it = std::find(positions.begin(), positions.end(), initial);
  double old_prob = initial_qp_it->getProb();
  // Entangled list is copied and then moved.
  initial_qp_it->setProb(old_prob / 2);
  initial_qp_it->setPosition(Position(new_real));
  auto insert_qp_it = initial_qp_it;
  auto new_qp_it = positions.insert(++insert_qp_it,
                                    QuantumPosition(new_fake,
                                                    old_prob / 2,
                                                    this));
  entanglement_log.addEntanglementsOfTo(*initial_qp_it, *new_qp_it);

  board.addChessmanOfIn(initial, final1);
  board.addChessmanIn(final2, this);
  board.pushToLog(initial.print() + " split to " + final1.print() + " and " +
                  final2.print());
}

void Chessman::merge(const Position &initial1, const Position &initial2,
                     const Position &final) {
  if (initial1 == initial2)
    throw ChessException("cannot merge from same square");

  std::list<Position> posible_moves;
  calculateMoves(initial1, posible_moves);
  posible_moves.push_back(initial1);
  auto final_it = std::find(posible_moves.begin(), posible_moves.end(),
                            final);
  if (final_it == posible_moves.end())
    throw ChessException("that chessman_ cant do that merge");
  moveValidationExceptionThrower(checkIsAValidMerge(initial1, final));

  calculateMoves(initial2, posible_moves);
  posible_moves.push_back(initial2);
  final_it = std::find(posible_moves.begin(), posible_moves.end(),
                       final);
  if (final_it == posible_moves.end())
    throw ChessException("that chessman_ cant do that merge");
  moveValidationExceptionThrower(checkIsAValidMerge(initial2, final));

  // Remove chessman_ of final places if there.
  if (board.getChessmanAt(final) == this)
    board.removeChessmanOf(final);

  /* If iterator 1 is real, then merge is saved in first position, if no
   * is saved in position of iterator 2 no matter what (if it 2 is real,
   * then is correct. */
  auto it1 = std::find(positions.begin(), positions.end(), initial1);
  auto it2 = std::find(positions.begin(), positions.end(), initial2);
  double prob = it1->getProb() + it2->getProb();

  entanglement_log.deleteEntanglementsWhichAreNotSharedBy(*it1, *it2);

  if (it1 == positions.begin()) {
    entanglement_log.deleteEntanglementsOf(*it2);
    positions.erase(it2);
    it1->setProb(prob);
    it1->setPosition(final);
  } else {
    entanglement_log.deleteEntanglementsOf(*it1);
    positions.erase(it1);
    it2->setProb(prob);
    it2->setPosition(final);
  }
  board.removeChessmanOf(initial1);
  board.removeChessmanOf(initial2);
  board.addChessmanIn(final, this);
  board.pushToLog(initial1.print() + " and " + initial2.print() +
                  " merged into " + final.print());
}

void Chessman::measure(const Position &position) {
  // If is not Quantum, then go back.
  if (!isQuantum())
    return;
  auto position_qp_it = std::find(positions.begin(),
                                  positions.end(), position);

  if (position_qp_it == positions.end())
    throw ChessException("chessman_ is not there");


  // If position is the first one, then leave as only real.
  if (position_qp_it == positions.begin()) {
    position_qp_it->setProb(1);
    // Measure the others, entangled with this and the other and remove.
    for (; position_qp_it != positions.end(); ++position_qp_it) {
      measureOthers(*position_qp_it);
      if (position_qp_it != positions.begin())
        board.removeChessmanOf(Position(*position_qp_it));
    }
    positions.erase(++positions.begin(), positions.end());
    board.pushToLog(position.print() + " measured, was there");
    return;
  }
  if (position_qp_it != positions.end()) {
    /* If is not real, then delete only it, un entangling
     * and measuring other. */
    measureOthers(*position_qp_it);
    double prob = position_qp_it->getProb();
    positions.erase(position_qp_it);
    board.removeChessmanOf(position);
    // Probability is propagated in the other positions.
    for (position_qp_it = positions.begin();
         position_qp_it != positions.end(); ++position_qp_it) {
      position_qp_it->setProb(position_qp_it->getProb() / (1 - prob));
    }
    board.pushToLog(position.print() + " measured, was not there");
    return;
  }
}

void Chessman::measureOthers(const QuantumPosition &quantum_position) {
  // If entangled appears only in this position, then measure.
  entanglement_log.measureEntanglements(*this, quantum_position);

  /* If other entangled appears in all positions but not in this one, then it
   * means that this is the position that was holding the other from
   * measuring.*/
  std::list<QuantumPosition *> positions_to_pass;
  for (auto &position: positions) {
    if (position != quantum_position) {
      QuantumPosition *position_ = &position;
      positions_to_pass.push_back(position_);
    }
  }
  entanglement_log.measureIfEntangledWithAllPositionsInList(positions_to_pass);
}

Chessman::MoveValidationStatus
Chessman::checkIsAValidMove(const Position &initial, const Position &final) {
  checkIsInBoardOrFail(initial);

  if (std::find(positions.begin(), positions.end(),
                initial) == positions.end())
    return CHESSMAN_NOT_IN_POSITION;

  if (this == board.getChessmanAt(final))
    return MOVING_TO_SQUARE_WITH_SAME_PIECE;
  Chessman *final_chessman = board.getChessmanAt(final);

  std::vector<Position> path;
  std::pair<Position, Chessman *> chessman_in_path;
  calculatePath(initial, final, path);

  if (!checkFreePath(path, chessman_in_path, false))
    return NON_FREE_PATH;

  getMiddlePathChessman(path, chessman_in_path);

  if (final_chessman && chessman_in_path.second)
    return MEASURING_AND_ENTANGLING;

  if (chessmanIsAlreadyEntangled(*chessman_in_path.second))
    return ENTANGLING_SAME_PIECE_TWO_TIMES;

  return OK;
}

Chessman::MoveValidationStatus
Chessman::checkIsAValidSplit(const Position &initial, const Position &final) {
  checkIsInBoardOrFail(initial);

  if (std::find(positions.begin(), positions.end(),
                initial) == positions.end())
    return CHESSMAN_NOT_IN_POSITION;

  std::vector<Position> path;
  std::pair<Position, Chessman *> chessman_in_path;

  calculatePath(initial, final, path);
  if (!checkFreePath(path, chessman_in_path, false))
    return NON_FREE_PATH;

  if (board.getChessmanAt(final))
    return SPLIT_TO_OCCUPIED_SQUARE;

  if (chessman_in_path.second)
    return SPLITTING_AND_ENTANGLING;

  if (getProbability(initial) / 2 < PRECISION_PROB)
    return SPLIT_LIMIT_REACHED;

  return OK;
}

Chessman::MoveValidationStatus
Chessman::checkIsAValidMerge(const Position &initial1, const Position &final) {
  checkIsInBoardOrFail(initial1);

  if (std::find(positions.begin(), positions.end(),
                initial1) == positions.end())
    return CHESSMAN_NOT_IN_POSITION;

  std::vector<Position> path;
  std::pair<Position, Chessman *> chessman_in_path;

  if (initial1 != final) {
    calculatePath(initial1, final, path);
    if (!checkFreePath(path, chessman_in_path, true))
      return NON_FREE_PATH;
  }

  if (chessman_in_path.second)
    return MERGING_AND_ENTANGLING;

  return OK;
}

void Chessman::calculatePossibleMoves(const Position &initial,
                                      std::list<Position> &possible_moves) {
  calculateMoves(initial, possible_moves);

  for (auto it = possible_moves.begin(); it != possible_moves.end();) {
    if (checkIsAValidMove(initial, *it)) {
      it = possible_moves.erase(it);
      continue;
    }
    ++it;
  }
}

void Chessman::calculatePossibleSplits(const Position &initial,
                                       std::list<Position> &possible_moves) {
  calculateMoves(initial, possible_moves);

  for (auto it = possible_moves.begin(); it != possible_moves.end();) {
    if (checkIsAValidSplit(initial, *it)) {
      it = possible_moves.erase(it);
      continue;
    }
    ++it;
  }
}

void Chessman::calculatePossibleMerges(const Position &initial,
                                       std::list<Position> &possible_moves) {
  if (getProbability(initial) == 1)
    return;

  calculateMoves(initial, possible_moves);
  possible_moves.push_back(initial);

  for (auto it = possible_moves.begin(); it != possible_moves.end();) {
    if (checkIsAValidMerge(initial, *it)) {
      it = possible_moves.erase(it);
      continue;
    }
    ++it;
  }
}

void Chessman::calculatePossibleMerges(const Position &initial1,
                                       const Position &initial2,
                                       std::list<Position> &possible_moves) {
  std::list<Position> aux;
  calculatePossibleMerges(initial1, possible_moves);
  calculatePossibleMerges(initial2, aux);

  for (auto it = possible_moves.begin(); it != possible_moves.end();) {
    if (std::find(aux.begin(), aux.end(), *it) == aux.end()) {
      it = possible_moves.erase(it);
      continue;
    }
    ++it;
  }
}

bool
Chessman::checkFreePath(const std::vector<Position> &path,
                        std::pair<Position, Chessman *> &chessman_in_path,
                        bool final_same_color_free) const {
  bool middle_path_free = getMiddlePathChessman(path, chessman_in_path);
  bool final_free = true;
  if (auto chessman = board.getChessmanAt(path.back())) {
    if (((chessman->white == white) ^ final_same_color_free)
        && !chessman->isQuantum())
      final_free = false;
  }
  return middle_path_free && final_free;
}

bool Chessman::getMiddlePathChessman(const std::vector<Position> &path,
                                     std::pair<Position, Chessman *> &chessman)
const {
  bool can_move = true;
  for (size_t i = 0; i < path.size() - 1; i++) {
    if (auto chessman_ = board.getChessmanAt(path[i])) {
      if (!can_move || !chessman_->isQuantum() || chessman_ == this)
        return false;
      chessman.first = path[i];
      chessman.second = chessman_;
      can_move = false;
    }
  }
  return true;
}

bool Chessman::isQuantum() const {
  return positions.size() > 1;
}

bool Chessman::isWhite() const {
  return white;
}

const QuantumPosition &Chessman::getPosition() const {
  return positions.front();
}

const QuantumPosition &Chessman::getPosition(size_t index) const {
  size_t i = 0;
  if (index >= positions.size())
    throw std::invalid_argument("index doesnt exist");
  for (auto &position: positions) {
    if (i == index)
      return position;
    i++;
  }
  return positions.front();
}

void Chessman::getAllPositions(std::list<Position> &output) const {
  for (auto it = positions.begin(); it != positions.end(); ++it)
    output.push_back(Position(*it));
}


size_t Chessman::positionsAmount() const {
  return positions.size();
}

void Chessman::calculatePath(const Position &initial,
                             const Position &final,
                             std::vector<Position> &path) const {
  if (initial == final)
    throw ChessException("cant calculate path between same square");
  if (initial.y() == final.y())
    calculateFilePath(initial, final, path);
  else if (initial.x() == final.x())
    calculateRowPath(initial, final, path);
  else if (abs((initial.x() - final.x()) / (initial.y() - final.y())) == 1)
    calculateDiagonalPath(initial, final, path);
  else
    throw ChessException("impossible move");
}

void Chessman::calculateFilePath(const Position &initial,
                                 const Position &final,
                                 std::vector<Position> &path) const {
  const Position &bottom = (initial.x() < final.x()) ? initial : final;
  const Position &top = (initial.x() < final.x()) ? final : initial;
  path = std::vector<Position>();
  path.reserve(7);

  for (uint8_t i = bottom.x() + 1; i < top.x(); i++)
    path.emplace_back(i, initial.y());
  path.push_back(final);
}

void Chessman::calculateRowPath(const Position &initial,
                                const Position &final,
                                std::vector<Position> &path) const {
  const Position &bottom = (initial.y() < final.y()) ? initial : final;
  const Position &top = (initial.y() < final.y()) ? final : initial;
  path = std::vector<Position>();
  path.reserve(7);

  for (uint8_t i = bottom.y() + 1; i < top.y(); i++)
    path.emplace_back(initial.x(), i);
  path.push_back(final);
}

void Chessman::calculateDiagonalPath(const Position &initial,
                                     const Position &final,
                                     std::vector<Position> &path) const {
  int8_t sum_x = (initial.x() < final.x()) ? 1 : -1;
  int8_t sum_y = (initial.y() < final.y()) ? 1 : -1;
  path = std::vector<Position>();
  path.reserve(6);

  for (int8_t i = initial.x() + sum_x, j = initial.y() + sum_y;
       i * sum_x < final.x() * sum_x && j * sum_y < final.y() * sum_y;
       i += sum_x, j += sum_y)
    path.emplace_back(i, j);
  path.push_back(final);
}

std::ostream &operator<<(std::ostream &os, const Chessman &chessman) {
  if (chessman.white)
    os << GREEN << chessman.charId() << RESET;
  else
    os << RED << chessman.charId() << RESET;
  return os;
}

double Chessman::getProbability(Position position_) {
  auto it = std::find(positions.begin(),
                      positions.end(), position_);
  if (it != positions.end())
    return it->getProb();
  throw std::invalid_argument("chessman_ is not there");
}

void Chessman::entangle(const Position &initial, const Position &final,
                        Chessman &other, const Position &other_position) {
  auto initial_qp_it = std::find(positions.begin(),
                                 positions.end(), initial);
  QuantumPosition &other_qp = *std::find(other.positions.begin(),
                                         other.positions.end(), other_position);
  // New probabilities calculation.
  double entangled_prob =
          other_qp.getProb();
  double initial_prob = initial_qp_it->getProb();
  double new_initial_prob = entangled_prob * initial_prob;
  double new_final_prob = initial_prob * (1 - entangled_prob);
  auto insert_qp_it = initial_qp_it;
  insert_qp_it++;

  if (new_initial_prob < PRECISION_PROB ||
      new_final_prob < PRECISION_PROB)
    throw ChessException("cannot split chessman_ anymore");

  /* If new quantum position created is real, then is placed at the
   * beginning of the positions list. */
  if (initial_qp_it == positions.begin() &&
      other.getPosition(0) != other_qp)
    insert_qp_it = positions.begin();

  initial_qp_it->setProb(new_initial_prob);
  insert_qp_it = positions.insert(insert_qp_it, QuantumPosition(final,
                                                                new_final_prob,
                                                                this));

  entanglement_log.addEntanglementsOfTo(*initial_qp_it, *insert_qp_it);

  entanglement_log.add(*insert_qp_it, other_qp);
}


void Chessman::checkIsInBoardOrFail(const Position &position) {
  Chessman *chessman = board.getChessmanAt(position);
  if (!chessman)
    throw ChessException("la pieza no esta en esa posicion en el tablero");
}

void Chessman::moveValidationExceptionThrower(MoveValidationStatus status) {
  switch (status) {
    case OK:
      return;
    case CHESSMAN_NOT_IN_POSITION:
      throw ChessException("chessman_ is not in that position");
    case MOVING_TO_SQUARE_WITH_SAME_PIECE:
      throw ChessException("cannot move to square with a fragment"
                           " of the same chessman_");
    case MEASURING_AND_ENTANGLING:
      throw ChessException("cannot measure and entangle"
                           " at same time");
    case ENTANGLING_SAME_PIECE_TWO_TIMES:
      throw ChessException("cannot entangle with same"
                           " piece two times");
    case MOVING_TO_SAME_SQUARE:
      throw ChessException("cannot move to same square");
    case NON_FREE_PATH:
      throw ChessException("path is not free");
    case SPLIT_TO_OCCUPIED_SQUARE:
      throw ChessException("splitting to occupied space");
    case SPLITTING_AND_ENTANGLING:
      throw ChessException("cannot split and entangle in"
                           " the same move");
    case SPLIT_LIMIT_REACHED:
      throw ChessException("cannot split more times that chessman_");
    case MERGING_AND_ENTANGLING:
      throw ChessException("cannot merge and entangle in"
                           " the same move");
    case PAWN_CANT_ENTANGLE:
      throw ChessException("pawn cannot entangle");
    case PAWN_CANT_SPLIT:
      throw ChessException("pawn cannot split");
    case PAWN_CANT_MERGE:
      throw ChessException("pawn cannot merge");
    case PAWN_CANT_EAT_LIKE_THAT:
      throw ChessException("pawn cannot eat like that");
    case PAWN_CANT_MEASURE_LIKE_THAT:
      throw ChessException("pawn cannot measure like that");
  }
}

bool Chessman::chessmanIsAlreadyEntangled(Chessman &chessman) {
  return entanglement_log.areEntangled(*this, chessman);
}

void Chessman::getEntangledPositions(std::list<Position> &output) {
  std::list<const Chessman *> entangled;
  entanglement_log.getEntangledOf(*this, entangled);
  for (auto &chessman: entangled)
    chessman->getAllPositions(output);
}







