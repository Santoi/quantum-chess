#ifndef QUANTUM_CHESS_PROJ_ERROR_LOG_H
#define QUANTUM_CHESS_PROJ_ERROR_LOG_H

#include "../../common/blocking_queue.h"
#include "../communication/remote_client_instructions.h"
#include  "../sdl/game_scene.h"
#include <utility>
#include <string>

#define MAX_MESSAGES 10

class ErrorLog {
private:
  GameScene &scene;

public:
  explicit ErrorLog(GameScene &scene);

  // Add an error message to the chat
  void addMessage(std::string message);

  // Erase all error messages from chat
  void clear();
};


#endif //QUANTUM_CHESS_PROJ_ERROR_LOG_H
