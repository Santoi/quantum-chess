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
  std::pair<PixelCoordinate, DrawableTile> current_tile;
  std::mutex mutex;

public:
  DrawableBoard(Window &window, const std::string &image, int width, int height,
                Font &font);

  ~DrawableBoard() = default;

  // Replace current chessmen with the chessmen vector in their new positions
  void load(std::vector<ChessmanData> &chessman_data_vector);

  // Set the given position's tile as a move tile
  void moveTile(const Position &pos);

  // Set the given position's tile as a quantum tile
  void quantumTile(const Position &pos);

  // Set the given position's tile as an entangled tile
  void entangledTile(const Position &pos);

  // Set the given position's tile as a split tile
  void splitTile(const Position &pos);

  // Set the given position's tile as a merge tile
  void mergeTile(const Position &pos);

  // Set the selected tile as selected
  void currentTile(const PixelCoordinate &coordinate);

  // Set the default tiles
  void setDefault();

  // Set the default tiles, except for the current tiles
  void setDefaultWithCurrent();

  // Render the current board
  void render(CoordinateTransformer &transformer, int width, int height);
};


#endif //QUANTUM_CHESS_PROJ_DRAWABLE_BOARD_H
