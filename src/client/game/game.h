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
#include "../sdl/sound/sound_handler.h"
#include "../sdl/scene.h"
#include <list>
#include <map>
#include <mutex>

class Sprite;

class RemoteClientInstruction;

class Game: public Scene {
private:
  Board board;
  BlockingQueue<RemoteClientInstruction> &send_queue;
  std::map<const PixelCoordinate, Sprite> sprites;
  CoordinateTransformer transformer;
  std::mutex mutex;
  ClientData::Role role;
  const SoundHandler &sound_handler;

public:
  Game(Window &window, BlockingQueue<RemoteClientInstruction> &send_queue_,
       ClientData::Role role_, const SoundHandler &sound_handler);

  void setScale(int scale_) override;

  bool isPixelInBoard(const PixelCoordinate &pixel);

  void setDefaultBoard();

  void moveTiles(const std::list<Position> &positions);

  void entangledTiles(const std::list<Position> &positions);

  void quantumTiles(const std::list<Position> &positions);

  void splitTiles(const std::list<Position> &positions);

  void mergeTiles(const std::list<Position> &positions);

  void moveChessman(PixelCoordinate &orig, PixelCoordinate &dest);

  void loadSprite(Sprite &sprite, int x, int y);

  void render() override;

  void load(std::vector<ChessmanData> &chessman_data_vector);

  void askMoveTiles(PixelCoordinate &coords);

  void askSplitTiles(PixelCoordinate &coords);

  void splitChessman(PixelCoordinate &from, PixelCoordinate &to1,
                     PixelCoordinate &to2);


  void askMergeTiles(PixelCoordinate &coords);

  void askMergeTiles(PixelCoordinate &coords1, PixelCoordinate &coords2);

  void playSplitSound();

  void playMovementSound();

  void playTakenPieceSound();

  void askEntangledTiles(PixelCoordinate &coords);

  void askQuantumTiles(PixelCoordinate &coords);
};


#endif //QUANTUM_CHESS_PROJ_GAME_H
