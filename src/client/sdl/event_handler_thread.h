#ifndef QUANTUM_CHESS_PROJ_EVENT_HANDLER_THREAD_H
#define QUANTUM_CHESS_PROJ_EVENT_HANDLER_THREAD_H

#include "../game/game.h"
#include "handler_thread.h"
#include "drawables/drawable_board.h"
#include "../../common/thread.h"
#include "../logic/text_entry.h"
#include <SDL2/SDL.h>

class EventHandlerThread : public HandlerThread {
private:
  Window &window;
  Game &game;
  TextEntry &text_entry;
  bool split, merge, first_click, second_click;
  PixelCoordinate penultimate_click;
  PixelCoordinate last_click;
  SDL_Event event;
  Chat &chat;

  void handleKeyDown();

  void handleKeyUp();

  void handleMouseButtonLeft(SDL_MouseButtonEvent &mouse);

  void handleMouseButtonRight(SDL_MouseButtonEvent &mouse);

  void handleWindowChange(SDL_WindowEvent &window_event);

  void handleTextInput(const std::string &text);

public:
  explicit EventHandlerThread(Window &window, Game &game,
                              Chat &chat_, TextEntry &text_entry);

  // Event loop
  void run() override;
};


#endif //QUANTUM_CHESS_PROJ_EVENT_HANDLER_THREAD_H
