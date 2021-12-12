#ifndef QUANTUM_CHESS_PROJ_GAME_H
#define QUANTUM_CHESS_PROJ_GAME_H

#include <vector>
#include "../sdl/drawables/drawable_board.h"
#include "../sdl/window.h"
#include "../sdl/pixel_coordinate.h"
#include "../sdl/sprite.h"
#include "../sdl/coordinate_transformer.h"
#include "../communication/remote_client_instructions.h"
#include "../../common/blocking_queue.h"
#include "../../common/client_data.h"
#include "../sdl/sound_handler.h"
#include <list>
#include <map>
#include <mutex>

class Sprite;

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

  // Reset board tiles
  void setDefaultBoard();

  // Reset board tiles, excluding the selected one
  void setDefaultBoardWithCurrent();

  // Tell board which tile was selected
  void currentTile(const PixelCoordinate &coordinate);

  // Tell board which tiles to mark as move tiles
  void moveTiles(const std::list<Position> &positions);

  // Tell board which tiles to mark as entangled tiles
  void entangledTiles(const std::list<Position> &positions);

  // Tell board which tiles to mark as quantum tiles
  void quantumTiles(const std::list<Position> &positions);

  // Tell board which tiles to mark as split tiles
  void splitTiles(const std::list<Position> &positions);

  // Tell board which tiles to mark as merge tiles
  void mergeTiles(const std::list<Position> &positions);

  // Move a chessman from source to destination positions
  void moveChessman(PixelCoordinate &orig, PixelCoordinate &dest);

  // Split a chessman into `to1` and `to2` positions
  void splitChessman(PixelCoordinate &from, PixelCoordinate &to1,
                     PixelCoordinate &to2);

  // Merge two chessmen into one tile
  void mergeChessman(PixelCoordinate &from1, PixelCoordinate &from2,
                     PixelCoordinate &to);

  // Load chessmen positions into the board
  void load(std::vector<ChessmanData> &chessman_data_vector);

  // Request posible move tiles to server
  void askMoveTiles(PixelCoordinate &coords);

  // Request posible split tiles to server
  void askSplitTiles(PixelCoordinate &coords);

  // Request posible merge tiles to server, for only 1 chessman
  void askMergeTiles(PixelCoordinate &coords);

  // Request posible merge tiles to server, when 2 chessmen are selected
  void askMergeTiles(PixelCoordinate &coords1, PixelCoordinate &coords2);

  // Request positions from entangled chessmen to the selected chessman
  void askEntangledTiles(PixelCoordinate &coords);

  // Request positions from the selected chessman's superpositions
  void askQuantumTiles(PixelCoordinate &coords);

  void playSplitSound();

  void playMergeSound();

  void playCaptureSound();

  void toggleSounds();

  void toggleMusic();

  ClientData::Role getPlayerRole();
};


#endif //QUANTUM_CHESS_PROJ_GAME_H
