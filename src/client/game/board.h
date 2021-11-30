#ifndef QUANTUM_CHESS_PROJ_BOARD_H
#define QUANTUM_CHESS_PROJ_BOARD_H

#include "drawable_chessman.h"
#include "drawable_tile.h"
#include "../sdl/chessman_sprite_repository.h"
#include "../position.h"
#include "../communication/chessman_data.h"
#include "../sdl/texture_sprite.h"
#include "../sdl/renderer.h"
#include "../sdl/window.h"
#include "../sdl/coordinate_transformer.h"
#include <map>
#include <string>
#include <vector>
#include <mutex>

class Renderer;

class Board {
private:
  Renderer &renderer;
  TextureSprite background;
  std::map<const Position, DrawableChessman> chessmen;
  std::map<const Position, DrawableTile> board;
  ChessmanSpriteRepository chessman_repository;
  TileSpriteRepository tile_repository;
  std::mutex mutex;

public:
  Board(Window &window, const std::string &image, int width, int height);

  ~Board() = default;

  void render();

  std::map<const Position, DrawableTile> getTiles();

  std::map<const Position, DrawableChessman> getChessmen();

  TextureSprite &getBackground();

  void load(std::vector<ChessmanData> &chessman_data_vector);

  void moveTile(const Position &pos);

  void quantumTile(const Position &pos);

  void entangledTile(const Position &pos);

  void splitTile(const Position &pos);

  void mergeTile(const Position &pos);

  void setDefault();

  void render(CoordinateTransformer &transformer, int width, int height);
};


#endif //QUANTUM_CHESS_PROJ_BOARD_H
