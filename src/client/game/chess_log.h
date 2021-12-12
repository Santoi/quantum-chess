#ifndef QUANTUM_CHESS_PROJ_CHESS_LOG_H
#define QUANTUM_CHESS_PROJ_CHESS_LOG_H

#include <utility>

#include "../../common/blocking_queue.h"
#include "../communication/remote_client_instructions.h"
#include  "../sdl/game_scene.h"

#define MAX_MESSAGES 10

class ChessLog {
private:
  GameScene &scene;

public:
  explicit ChessLog(GameScene &scene);

  // Add a log message to the chat
  void addMessage(std::string message);
};


#endif //QUANTUM_CHESS_PROJ_CHESS_LOG_H
