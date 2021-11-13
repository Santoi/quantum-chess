#ifndef QUANTUM_CHESS_PROJ_BOARD_H
#define QUANTUM_CHESS_PROJ_BOARD_H

#include "sprite.h"
#include "chessman.h"
#include "tile.h"
#include "position.h"
#include <SDL2pp/SDL2pp.hh>
#include <map>

class Board {
private:
  SDL2pp::Renderer &renderer;
  Sprite sprite;
  std::map<const Position, Chessman> chessmen;
  std::map<const Position, Tile> board;

public:
  explicit Board(SDL2pp::Renderer &renderer);
  ~Board() = default;

  void render();

  void moveTile(int x, int y);
};


#endif //QUANTUM_CHESS_PROJ_BOARD_H
