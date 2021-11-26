#ifndef QUANTUM_CHESS_PROJ_EVENT_HANDLER_THREAD_H
#define QUANTUM_CHESS_PROJ_EVENT_HANDLER_THREAD_H

#include "../game/game.h"
#include "../game/board.h"
#include "handler_thread.h"
#include <SDL2/SDL.h>

class EventHandlerThread : public HandlerThread {
private:
  Game &game;
  bool split, merge, first_click, second_click;
  PixelCoordinate penultimate_click;
  PixelCoordinate last_click;
  SDL_Event event;

  void handleKeyDown();

  void handleKeyUp();

  void handleMouseButtonLeft(SDL_MouseButtonEvent &mouse);

public:
  explicit EventHandlerThread(Game &game);

  // Event loop
  void run() override;

  bool isOpen();

  void handleMouseButtonRight(SDL_MouseButtonEvent &mouse);
};


#endif //QUANTUM_CHESS_PROJ_EVENT_HANDLER_THREAD_H
