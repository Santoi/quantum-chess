#include "board.h"
#include "renderer.h"
#include <map>

void Board::create(Renderer &renderer) {
  for (size_t i = 0; i < 8; i++) {
    for (size_t j = 0; j < 8; j++) {
      const Position position(i, j);
      Tile tile(renderer, position.isEven());
      board.insert(std::move(std::pair<const Position, Tile>(position, std::move(tile))));
    }
  }
}

void Board::render() {
  for (auto & it : board) {
    it.second.render(it.first.x(), it.first.y());
  }
  for (auto & it : chessmen) {
    it.second.render(it.first.x(), it.first.y());
  }
}

void Board::createChessman(const Position &dest, Chessman &chessman) {
  chessmen.insert(std::move(std::pair<const Position, Chessman>(dest, std::move(chessman))));
}

void Board::moveChessman(Position &orig, Position &dest) {
  Chessman &chessman = chessmen.at(orig); // TODO: catch exception
  chessmen.erase(orig);
  chessmen.insert(std::move(std::pair<const Position, Chessman>(dest, std::move(chessman))));
}

void Board::moveTile(int x, int y) {
  const Position pos(x, y);
  board.at(pos).loadMove();
}

void Board::setDefault() {
  for (auto & it : board) {
    it.second.loadDefault();
  }
}

std::map<const Position, Tile>& Board::getTiles() {
  return board;
}

std::map<const Position, Chessman>& Board::getChessmen() {
  return chessmen;
}
