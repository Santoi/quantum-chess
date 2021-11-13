#include "board.h"
#include <SDL2pp/SDL2pp.hh>
#include <map>

Board::Board(SDL2pp::Renderer &renderer): renderer(renderer), sprite(renderer) {
  for (size_t i = 0; i < 8; i++) {
    for (size_t j = 0; j < 8; j++) {
      const Position position(i, j);
      Tile square(renderer, position.isEven());
      board.insert(std::pair<const Position, Tile>(position, std::move(square)));
    }
  }
}

void Board::render() {
  for (auto & it : board) {
    it.second.render(it.first.x(), it.first.y());
  }
}

void Board::moveTile(int x, int y) {
  const Position pos(x, y);
  board.at(pos).renderMove();
}