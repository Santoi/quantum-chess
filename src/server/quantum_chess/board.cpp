#include "board.h"
#include "../../common/chess_exception.h"
#include "chessman/king.h"
#include "chessman/queen.h"
#include "chessman/tower.h"
#include "chessman/bishop.h"
#include "chessman/knight.h"
#include "chessman/pawn.h"
#include "client_data.h"
#include <utility>
#include <algorithm>
#include <memory>
#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <vector>

Board::Board()
    : chessmen(), board(), next_white(true), coin(), entanglement_log(),
      finished(false) {}

Board::Board(bool random)
    : chessmen(), board(), next_white(true), coin(random),
      entanglement_log(),
      finished(false) {}

void Board::addNewChessman(char chessman_, Position position_,
                           bool white_) {
  std::unique_ptr<Chessman> new_chessman = createChessman(chessman_,
                                                          position_,
                                                          white_);
  Chessman *ptr = new_chessman.get();
  chessmen.push_back(std::move(new_chessman));

  for (size_t i = 0; i < ptr->positionsAmount(); i++) {
    Position position = Position(ptr->getPosition(i));
    if (board.count(Position(position)))
      throw ChessException("there is a chessman_ there already");
    board.insert(std::make_pair(Position(position),
                                ptr));
  }
}

bool
Board::move(const Position &initial, const Position &final, bool player_white) {
  if (finished)
    throw ChessException("game over");
  if (player_white != next_white)
    throw ChessException("it is not your turn!");
  Chessman *chessman = getChessmanAt(initial);
  if (!chessman)
    throw ChessException("there is no chessman_ there");
  if (chessman->isWhite() != player_white)
    throw ChessException("you cannot move a chessman_"
                         " of the other player");
  bool capture = chessman->move(initial, final);
  next_white = !next_white;
  return capture;
}

void Board::split(const Position &initial, const Position &pos1,
                  const Position &pos2, bool player_white) {
  if (finished)
    throw ChessException("game over");
  if (player_white != next_white)
    throw ChessException("it is not your turn!");
  Chessman *chessman = getChessmanAt(initial);
  if (!chessman)
    throw ChessException("there is no chessman_ there");
  if (chessman->isWhite() != player_white)
    throw ChessException("you cannot move a chessman_"
                         " of the other player");
  chessman->split(initial, pos1, pos2);
  next_white = !next_white;
}

void Board::merge(const Position &initial1, const Position &initial2,
                  const Position &final, bool player_white) {
  if (finished)
    throw ChessException("game over");
  if (player_white != next_white)
    throw ChessException("it is not your turn!");
  Chessman *chessman_1 = getChessmanAt(initial1),
      *chessman_2 = getChessmanAt(initial2);
  if (!chessman_1 || !chessman_2)
    throw ChessException("there is no chessman_ there");
  if (chessman_1 != chessman_2)
    throw ChessException("you re trying to merge two different chessmen");
  if (chessman_1->isWhite() != player_white ||
      chessman_2->isWhite() != player_white)
    throw ChessException("you cannot move a chessman_ of the other"
                         " player");
  chessman_1->merge(initial1, initial2, final);
  next_white = !next_white;
}

void Board::getPossibleMovesOf(const Position &position,
                               std::list<Position> &output) {
  Chessman *chessman = getChessmanAt(position);
  if (chessman)
    chessman->calculatePossibleMoves(position, output);
}

void Board::getPossibleSplitsOf(const Position &position,
                                std::list<Position> &output) {
  Chessman *chessman = getChessmanAt(position);
  if (chessman)
    chessman->calculatePossibleSplits(position, output);
}

void Board::getPossibleMergesOf(const Position &position,
                                std::list<Position> &output) {
  Chessman *chessman = getChessmanAt(position);
  if (chessman)
    chessman->calculatePossibleMerges(position, output);
}

void
Board::getPossibleMergesOf(const Position &position1, const Position &position2,
                           std::list<Position> &output) {
  Chessman *chessman = getChessmanAt(position1);
  if (chessman)
    chessman->calculatePossibleMerges(position1, position2, output);
}

void
Board::getPositionsOf(const Position &position1, std::list<Position> &output) {
  Chessman *chessman = getChessmanAt(position1);
  if (chessman)
    chessman->getAllPositions(output);
}

void
Board::getEntangledOf(const Position &position1, std::list<Position> &output) {
  Chessman *chessman = getChessmanAt(position1);
  if (chessman)
    chessman->getEntangledPositions(output);
}

void Board::addChessmanIn(const Position &position, Chessman *chessman) {
  if (board.count(position))
    throw ChessException("there is a chessman_ there already");
  board.insert(std::pair<Position, Chessman *>(Position(position),
                                               chessman));
}

void Board::removeChessmanOf(const Position &position) {
  if (board.count(position))
    board.erase(position);
}

void Board::addChessmanOfIn(const Position &initial, const Position &final) {
  Chessman *chessman = getChessmanAt(initial);
  if (!chessman)
    throw ChessException("there isn a chessman_ there");
  if (board.count(final))
    throw ChessException("there is a chessman_ there already");
  board.erase(initial);
  board.insert(std::pair<Position, Chessman *>(final, chessman));
}

Chessman *Board::getChessmanAt(const Position &position) {
  if (board.count(position))
    return board.at(position);
  return nullptr;
}

bool Board::isNextWhite() const {
  return next_white;
}

bool Board::isThere(Chessman *chessman) {
  return std::any_of(board.begin(), board.end(),
                     [&](std::pair<const Position, Chessman *> pair) {
                       return pair.second == chessman;
                     });
}

void
Board::loadVectorOfSquareData(std::vector<SquareData> &data) {
  data.reserve(board.size());
  for (auto &it: board) {
    data.emplace_back(it.second->charId(), it.second->isWhite(), it.first,
                      it.second->getProbability(it.first));
  }
}

std::unique_ptr<Chessman> Board::createChessman(char chessman_,
                                                Position position_,
                                                bool white_) {
  Chessman *pointer = nullptr;
  switch (chessman_) {
    case 'K':
      pointer = new King(position_, white_, *this, entanglement_log);
      break;
    case 'Q':
      pointer = new Queen(position_, white_, *this, entanglement_log);
      break;
    case 'T':
      pointer = new Tower(position_, white_, *this, entanglement_log);
      break;
    case 'B':
      pointer = new Bishop(position_, white_, *this, entanglement_log);
      break;
    case 'H':
      pointer = new Knight(position_, white_, *this, entanglement_log);
      break;
    case 'P':
      pointer = new Pawn(position_, white_, *this, entanglement_log);
      break;
    default:
      throw std::invalid_argument("that character doesnt represent any"
                                  "chessman_");
  }
  if (!pointer)
    throw std::runtime_error("cannot allocate memory for chessman_");
  return std::unique_ptr<Chessman>(pointer);
}

void Board::load(std::ifstream &file) {
  std::string line;
  file.seekg(0);
  while (!file.eof() && file.peek() != EOF) {
    std::getline(file, line);
    if (line.empty() || line[0] == LOADER_COMMENT)
      continue;
    std::stringstream iss(line);
    char chessman, color;
    uint8_t x, y;
    iss >> chessman >> x >> y >> color;
    x -= 'A';
    y = y - '0' - 1;
    if (color != 'W' && color != 'B')
      throw std::invalid_argument("invalid color");
    Position position(x, y);
    if (getChessmanAt(position))
      throw std::invalid_argument("position occupied twice in file");
    addNewChessman(chessman, position, color == 'W');
  }
}

bool Board::flipACoin() {
  return coin.flip();
}

void Board::endGame() {
  finished = true;
}

void Board::pushToLog(std::string string) {
  chess_log.push(std::move(string));
}

void Board::popLog(std::list<std::string> &popped) {
  while (!chess_log.empty()) {
    popped.push_back(std::move(chess_log.top()));
    chess_log.pop();
  }
}
