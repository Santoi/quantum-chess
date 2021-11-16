#ifndef QUANTUM_CHESS_PROJ_EVENT_HANDLER_H
#define QUANTUM_CHESS_PROJ_EVENT_HANDLER_H

#include "scene.h"
#include <SDL2/SDL.h>

class EventHandler {
private:
  SDL_Event event;

public:
  EventHandler() = default;
  bool handleEvents(Scene &scene, Board &board);
  void handleMouse();
};


#endif //QUANTUM_CHESS_PROJ_EVENT_HANDLER_H
