#include "board.h"
#include "chess_exception.h"
#include "chessman/king.h"
#include "chessman/queen.h"
#include "chessman/tower.h"
#include "chessman/bishop.h"
#include "chessman/knight.h"
#include "chessman/pawn.h"
#include <utility>
#include <algorithm>
#include <memory>
#include <sstream>
#include <fstream>

Board::Board() : chessmen(), board(), next_white(true), coin() {}

Board::Board(int seed) : chessmen(), board(), next_white(true), coin(seed) {}

// TODO interfaz cuantica, dejarla a punto.

// TODO testear BOARD.

void Board::addNewChessman(char chessman_, Position position_,
                           bool white_) {
  std::unique_ptr<Chessman> new_chessman = createChessman(chessman_,
                                                          position_,
                                                          white_);
  Chessman *ptr = new_chessman.get();
  chessmen.push_back(std::move(new_chessman));

  for (size_t i = 0; i < ptr->countPositions(); i++) {
    Position position = Position(ptr->getPosition(i));
    if (board.count(Position(position)))
      throw ChessException("ya hay una pieza alli");
    board.insert(std::make_pair(Position(position),
                                ptr));
  }
}

void
Board::move(const Position &initial, const Position &final, bool player_white) {
  if (player_white != next_white)
    throw ChessException("is not your turn!");
  Chessman *chessman = getChessmanAt(initial);
  if (!chessman)
    throw ChessException("no hay ninguna pieza ahi");
  if (chessman->isWhite() != player_white)
    throw ChessException("you cannot move a chessman"
                         " of the other player");
  chessman->move(initial, final);
  next_white = !next_white;
}

void Board::split(const Position &initial, const Position &pos1,
                  const Position &pos2, bool player_white) {
  if (player_white != next_white)
    throw ChessException("is not your turn!");
  Chessman *chessman = getChessmanAt(initial);
  if (!chessman)
    throw ChessException("no hay ninguna pieza alli");
  if (chessman->isWhite() != player_white)
    throw ChessException("you cannot move a chessman"
                         " of the other player");
  chessman->split(initial, pos1, pos2);
  next_white = !next_white;
}

void Board::merge(const Position &initial1, const Position &initial2,
                  const Position &final, bool player_white) {
  if (player_white != next_white)
    throw ChessException("is not your turn!");
  Chessman *chessman_1 = getChessmanAt(initial1),
          *chessman_2 = getChessmanAt(initial2);
  if (!chessman_1)
    throw ChessException("no hay ninguna pieza alli");
  if (!chessman_2)
    throw ChessException("no hay ninguna pieza alli");
  if (chessman_1 != chessman_2)
    throw ChessException("se esta tratando de unir dos piezas distintas");
  if (chessman_1->isWhite() != player_white ||
      chessman_2->isWhite() != player_white)
    throw ChessException("you cannot move a chessman"
                         " of the other player");
  chessman_1->merge(initial1, initial2, final);
  next_white = !next_white;
}

std::list<Position> Board::getPossibleMovesOf(const Position &position) {
  std::list<Position> output;
  Chessman *chessman = getChessmanAt(position);
  if (chessman)
    chessman->calculatePosibleMoves(position, output);
  return output;
}

std::list<Position> Board::getPossibleSplitsOf(const Position &position) {
  std::list<Position> output;
  Chessman *chessman = getChessmanAt(position);
  if (chessman)
    chessman->calculatePosibleSplits(position, output);
  return output;
}

std::list<Position> Board::getPossibleMergesOf(const Position &position) {
  std::list<Position> output;
  Chessman *chessman = getChessmanAt(position);
  if (chessman)
    chessman->calculatePosibleMerges(position, output);
  return output;
}

std::list<Position> Board::getPossibleMergesOf(const Position &position1,
                                               const Position &position2) {
  std::list<Position> output;
  Chessman *chessman = getChessmanAt(position1);
  if (chessman)
    chessman->calculatePosibleMerges(position1, position2, output);
  return output;
}

std::list<Position> Board::getPositionsOf(const Position &position1) {
  std::list<Position> output;
  Chessman *chessman = getChessmanAt(position1);
  if (chessman)
    chessman->getAllPositions(output);
  return output;
}

std::list<Position> Board::getEntangledOf(const Position &position1) {
  std::list<Position> output;
  Chessman *chessman = getChessmanAt(position1);
  if (chessman)
    chessman->getEntangledPositions(output);
  return output;
}

void Board::addChessmanIn(const Position &position, Chessman *chessman) {
  if (board.count(position))
    throw ChessException("ya hay una pieza alli");
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
    throw ChessException("no hay ninguna pieza ahi");
  if (board.count(final))
    throw ChessException("ya hay una pieza alli");
  board.erase(initial);
  board.insert(std::pair<Position, Chessman *>(final, chessman));
}

void Board::addChessmanOfIn(const Position &initial, const Position &pos1,
                            const Position &pos2) {
  Chessman *chessman = getChessmanAt(initial);
  if (!chessman)
    throw ChessException("no hay ninguna pieza ahi");
  if (board.count(pos1) || board.count(pos2))
    throw ChessException("ya hay una pieza alli");
  board.erase(initial);
  board.insert(std::pair<Position, Chessman *>(pos1, chessman));
  board.insert(std::pair<Position, Chessman *>(pos2, chessman));
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
Board::loadVectors(std::vector<char> &characters_, std::vector<bool> &colors_,
                   std::vector<Position> &positions_,
                   std::vector<double> &probabilities) {
  // TODO hacerlo un paquete solo.
  characters_.reserve(board.size());
  colors_.reserve(board.size());
  positions_.reserve(board.size());
  probabilities.reserve(board.size());
  for (auto it = board.begin(); it != board.end(); ++it) {
    characters_.push_back(it->second->print());
    positions_.push_back(it->first);
    colors_.push_back(it->second->isWhite());
    probabilities.push_back(it->second->getProbability(it->first));
  }
}

std::unique_ptr<Chessman> Board::createChessman(char chessman_,
                                                Position position_,
                                                bool white_) {
  Chessman *pointer = nullptr;
  switch (chessman_) {
    case 'K':
      pointer = new King(position_, white_, *this);
      break;
    case 'Q':
      pointer = new Queen(position_, white_, *this);
      break;
    case 'T':
      pointer = new Tower(position_, white_, *this);
      break;
    case 'B':
      pointer = new Bishop(position_, white_, *this);
      break;
    case 'H':
      pointer = new Knight(position_, white_, *this);
      break;
    case 'P':
      pointer = new Pawn(position_, white_, *this);
      break;
    default:
      throw ChessException("esa letra no "
                           "representa ninguna pieza");
  }
  if (!pointer)
    throw std::runtime_error("cannot allocate memory for chessman");
  return std::unique_ptr<Chessman>(pointer);
}

void Board::load(const std::string &filename) {
  std::ifstream file(filename, std::ios_base::in);
  std::string line;
  while (!file.eof() && file.peek() != EOF) {
    std::getline(file, line);
    if (line.empty())
      continue;
    if (line[0] == LOADER_COMMENT)
      continue;
    std::stringstream iss(line);
    char chessman, color;
    uint8_t x, y;
    iss >> chessman >> x >> y >> color;
    x -= 'A';
    y = y - '0' - 1;
    if (color != 'W' && color != 'B')
      throw std::invalid_argument("invalid color");
    addNewChessman(chessman, Position(x, y), color == 'W');
  }
}

bool Board::flipACoin() {
  return coin.flip();
}
