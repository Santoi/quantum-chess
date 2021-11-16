#ifndef QUANTUM_CHESS_PROJ_SCENE_H
#define QUANTUM_CHESS_PROJ_SCENE_H

#include "pixel_coordinate.h"
#include "sprite.h"
#include "board.h"
#include "coordinate_transformer.h"
#include <list>
#include <map>

class Sprite;

class Scene {
private:
  int scale;
  Board &board;
  std::map<const PixelCoordinate, Sprite> sprites;
  CoordinateTransformer transformer;

public:
  Scene(int height, Board &board);
  void setScale(int scale_);

  void setDefaultBoard();

  void moveTiles(const std::list<Position> &positions);
  void entangledTiles(const std::list<Position> &positions);
  void quantumTiles(const std::list<Position> &positions);
  void splitTiles(const std::list<Position> &positions);
  void mergeTiles(const std::list<Position> &positions);

  void moveChessman(PixelCoordinate &orig, PixelCoordinate &dest);

  void loadSprite(Sprite &sprite, int x, int y);
  void render();
};


#endif //QUANTUM_CHESS_PROJ_SCENE_H
