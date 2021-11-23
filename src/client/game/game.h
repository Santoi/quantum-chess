#ifndef QUANTUM_CHESS_PROJ_GAME_H
#define QUANTUM_CHESS_PROJ_GAME_H

#include "../sdl/pixel_coordinate.h"
#include "../sdl/sprite.h"
#include "../sdl/window.h"
#include "board.h"
#include "../sdl/coordinate_transformer.h"
#include "../communication/remote_client_instructions.h"
#include "../../common/src/blocking_queue.h"
#include "../../common/src/client_data.h"
#include <list>
#include <map>
#include <mutex>

class Sprite;

class RemoteClientInstruction;

class Game {
private:
  int scale;
  Board board;
  BlockingQueue<RemoteClientInstruction> &send_queue;
  std::map<const PixelCoordinate, Sprite> sprites;
  CoordinateTransformer transformer;
  std::mutex mutex;
  ClientData::Role role;

public:
  Game(Window &window, BlockingQueue<RemoteClientInstruction> &send_queue_,
       ClientData::Role role_);

  void setScale(int scale_);

  bool isPixelInBoard(const PixelCoordinate &pixel);

  void setDefaultBoard();

  void moveTiles(const std::list<Position> &positions);

  void entangledTiles(const std::list<Position> &positions);

  void quantumTiles(const std::list<Position> &positions);

  void splitTiles(const std::list<Position> &positions);

  void mergeTiles(const std::list<Position> &positions);

  void moveChessman(PixelCoordinate &orig, PixelCoordinate &dest);

  void loadSprite(Sprite &sprite, int x, int y);

  void render();

  void load(std::vector<ChessmanData> &chessman_data_vector);

  void askMoveTiles(PixelCoordinate &coords);

  void askSplitTiles(PixelCoordinate &coords);

  void splitChessman(PixelCoordinate &from, PixelCoordinate &to1,
                     PixelCoordinate &to2);
};


#endif //QUANTUM_CHESS_PROJ_GAME_H
