#ifndef QUANTUM_CHESS_PROJ_EVENT_HANDLER_H
#define QUANTUM_CHESS_PROJ_EVENT_HANDLER_H

#include "scene.h"
#include "../game/board.h"
#include "chat/text_entry.h"
#include <SDL2/SDL.h>
#include <map>

class EventHandler {
private:
  bool split, merge, move;
  PixelCoordinate last;
  SDL_Event event;
  SDL_Keycode keyboard;

public:
  EventHandler();

  // Event loop
  bool handleEvents(Scene &scene, Board &board);

  bool writeMessage(Renderer &renderer, TextEntry &text_entry);
//  void handleMouse();
};


#endif //QUANTUM_CHESS_PROJ_EVENT_HANDLER_H
