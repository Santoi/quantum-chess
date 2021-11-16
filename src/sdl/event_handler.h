#ifndef QUANTUM_CHESS_PROJ_EVENT_HANDLER_H
#define QUANTUM_CHESS_PROJ_EVENT_HANDLER_H

#include "scene.h"
#include "board.h"
#include <SDL2/SDL.h>

class EventHandler {
private:
  bool split, merge, move;
  PixelCoordinate last;
  SDL_Event event;

public:
  EventHandler();
  // Event loop
  bool handleEvents(Scene &scene, Board &board);
//  void handleMouse();
};


#endif //QUANTUM_CHESS_PROJ_EVENT_HANDLER_H
