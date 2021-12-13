#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_BOARD_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_BOARD_H

#include "drawable_chessman.h"
#include "drawable_tile.h"
#include "../sprite_repositories/chessman_sprite_repository.h"
#include "../../game/position.h"
#include "../../communication/chessman_data.h"
#include "../texture_sprite.h"
#include "../renderer.h"
#include "../window.h"
#include "drawable_text.h"
#include "../sprite_repositories/text_sprite_repository.h"
#include "../coordinate_transformer.h"
#include <map>
#include <string>
#include <vector>
#include <mutex>

class Renderer;

class DrawableBoard {
private:
  Renderer &renderer;
  TextureSprite background;
  std::map<const Position, DrawableChessman> chessmen;
  std::map<const Position, DrawableTile> board;
  std::map<const Position, DrawableText> positions;
  ChessmanSpriteRepository chessman_repository;
  TileSpriteRepository tile_repository;
  TextSpriteRepository text_repository;
  bool current;
  std::pair<Position, DrawableTile> current_tile;
  std::mutex mutex;

public:
  DrawableBoard(Window &window, const std::string &image, int width, int height,
                Font &font);

  ~DrawableBoard() = default;

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

  void currentTile(const Position &position);

  void setDefaultWithCurrent();
};


#endif //QUANTUM_CHESS_PROJ_DRAWABLE_BOARD_H
