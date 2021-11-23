#ifndef QUANTUM_CHESS_PROJ_EVENT_HANDLER_THREAD_H
#define QUANTUM_CHESS_PROJ_EVENT_HANDLER_THREAD_H

#include "../game/game.h"
#include "../game/board.h"
#include "../../common/src/thread.h"
#include <SDL2/SDL.h>
#include <atomic>

class EventHandlerThread : public Thread {
private:
  std::atomic<bool> open;
  Game &game;
  bool split, merge, move;
  PixelCoordinate last;
  SDL_Event event;

  void handleKeyDown();

  void handleKeyUp();

  void handleMouseButtonLeft(SDL_MouseButtonEvent &mouse);

public:
  explicit EventHandlerThread(Game &game);

  // Event loop
  void run() override;

  bool isOpen();
};


#endif //QUANTUM_CHESS_PROJ_EVENT_HANDLER_THREAD_H
