#ifndef QUANTUM_CHESS_PROJ_BOARD_H
#define QUANTUM_CHESS_PROJ_BOARD_H

#include "../sdl/renderer.h"
#include "../sdl/sprite.h"
#include "chessman.h"
#include "tile.h"
#include "../position.h"
#include "../communication/chessman_data.h"
#include <map>
#include <string>
#include <vector>

class Board {
private:
  Renderer & renderer;
  Sprite background;
  std::map<const Position, Chessman> chessmen;
  std::map<const Position, Tile> board;

public:
  Board(Renderer &renderer_, const std::string &image, int width, int height);
  ~Board() = default;

  void render();

  std::map<const Position, Tile>& getTiles();
  std::map<const Position, Chessman>& getChessmen();
  Sprite& getBackground();

  void load(std::vector<ChessmanData> & chessman_data_vector);
  void moveChessman(Position &orig, Position &dest);

  void moveTile(const Position &pos);
  void quantumTile(const Position &pos);
  void entangledTile(const Position &pos);
  void splitTile(const Position &pos);
  void mergeTile(const Position &pos);

  void setDefault();
};


#endif //QUANTUM_CHESS_PROJ_BOARD_H
