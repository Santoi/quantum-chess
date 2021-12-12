#ifndef QUANTUM_CHESS_PROJ_ERROR_LOG_H
#define QUANTUM_CHESS_PROJ_ERROR_LOG_H

#include <utility>

#include "../../common/blocking_queue.h"
#include "../communication/remote_client_instructions.h"
#include  "../sdl/game_scene.h"

#define MAX_MESSAGES 10

class ErrorLog {
private:
  GameScene &scene;

public:
  explicit ErrorLog(GameScene &scene);

  void addMessage(std::string message);

  void clear();
};


#endif //QUANTUM_CHESS_PROJ_ERROR_LOG_H
