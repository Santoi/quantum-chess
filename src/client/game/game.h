#ifndef QUANTUM_CHESS_PROJ_GAME_H
#define QUANTUM_CHESS_PROJ_GAME_H

#include <vector>
#include "drawable_board.h"
#include "../sdl/window.h"
#include "../sdl/pixel_coordinate.h"
#include "../sdl/sprite.h"
#include "../sdl/coordinate_transformer.h"
#include "../communication/remote_client_instructions.h"
#include "../../common/src/blocking_queue.h"
#include "../../common/src/client_data.h"
#include "../sdl/sound/sound_handler.h"
#include <list>
#include <map>
#include <mutex>

class TextureSprite;

class RemoteClientInstruction;

class Game {
private:
  int x_scale, y_scale;
  DrawableBoard board;
  BlockingQueue<RemoteClientInstruction> &send_queue;
  CoordinateTransformer transformer;
  std::mutex mutex;
  ClientData::Role role;
  SoundHandler &sound_handler;

public:
  Game(Window &window,
       BlockingQueue<RemoteClientInstruction> &send_queue_,
       ClientData::Role role_, Font &font);

  void setScale(int x_scale_, int y_scale_);

  DrawableBoard &getBoard();

  bool isPixelInBoard(const PixelCoordinate &pixel);

  void setDefaultBoard();

  void moveTiles(const std::list<Position> &positions);

  void entangledTiles(const std::list<Position> &positions);

  void quantumTiles(const std::list<Position> &positions);

  void splitTiles(const std::list<Position> &positions);

  void mergeTiles(const std::list<Position> &positions);

  void moveChessman(PixelCoordinate &orig, PixelCoordinate &dest);

  void load(std::vector<ChessmanData> &chessman_data_vector);

  void askMoveTiles(PixelCoordinate &coords);

  void askSplitTiles(PixelCoordinate &coords);

  void splitChessman(PixelCoordinate &from, PixelCoordinate &to1,
                     PixelCoordinate &to2);


  void askMergeTiles(PixelCoordinate &coords);

  void askMergeTiles(PixelCoordinate &coords1, PixelCoordinate &coords2);

  void playSplitSound();

  void playMergeSound();

  void playCaptureSound();

  void askEntangledTiles(PixelCoordinate &coords);

  void askQuantumTiles(PixelCoordinate &coords);

  void mergeChessman(PixelCoordinate &from1, PixelCoordinate &from2,
                     PixelCoordinate &to);

  void toggleSounds();

  void toggleMusic();

  void currentTile(const PixelCoordinate &coordinate);
};


#endif //QUANTUM_CHESS_PROJ_GAME_H
