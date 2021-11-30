#ifndef QUANTUM_CHESS_PROJ_TURN_LOG_H
#define QUANTUM_CHESS_PROJ_TURN_LOG_H

#include <utility>

#include "../../common/src/blocking_queue.h"
#include "../communication/remote_client_instructions.h"
#include  "../sdl/scene.h"

#define MAX_MESSAGES 10

class TurnLog {
private:
  Scene &scene;

public:
  explicit TurnLog(Scene &scene);

  void changeTurn(bool white);
};


#endif //QUANTUM_CHESS_PROJ_TURN_LOG_H
