#ifndef QUANTUM_CHESS_PROJ_TURN_LOG_H
#define QUANTUM_CHESS_PROJ_TURN_LOG_H

#include <utility>

#include "../../common/blocking_queue.h"
#include "../communication/remote_client_instructions.h"
#include  "../sdl/game_scene.h"

#define MAX_MESSAGES 10

class TurnLog {
private:
  GameScene &scene;

public:
  explicit TurnLog(GameScene &scene);

  // Shows whose turn it is and player's role in game chat
  void changeTurn(bool white, ClientData::Role role);
};


#endif //QUANTUM_CHESS_PROJ_TURN_LOG_H
