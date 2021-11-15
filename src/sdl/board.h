#ifndef QUANTUM_CHESS_PROJ_BOARD_H
#define QUANTUM_CHESS_PROJ_BOARD_H

#include "renderer.h"
#include "sprite.h"
#include "chessman.h"
#include "tile.h"
#include "position.h"
#include <map>

class Board {
private:
  std::map<const Position, Chessman> chessmen;
  std::map<const Position, Tile> board;

public:
  Board() = default;
  ~Board() = default;

  void create(Renderer &renderer);
  void render();

  std::map<const Position, Tile>& getTiles();
  std::map<const Position, Chessman>& getChessmen();

  void createChessman(const Position &dest, Chessman &chessman);
  void moveChessman(Position &orig, Position &dest);

  void moveTile(int x, int y);

  void setDefault();
};


#endif //QUANTUM_CHESS_PROJ_BOARD_H
