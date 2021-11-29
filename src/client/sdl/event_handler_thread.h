#ifndef QUANTUM_CHESS_PROJ_EVENT_HANDLER_THREAD_H
#define QUANTUM_CHESS_PROJ_EVENT_HANDLER_THREAD_H

#include "../game/game.h"
#include "../game/board.h"
#include "../../common/src/thread.h"
#include "chat/text_entry.h"
#include <SDL2/SDL.h>
#include <atomic>

class EventHandlerThread : public Thread {
private:
  Window &window;
  std::atomic<bool> open;
  Game &game;
  TextEntry text_entry; // TODO MATI: replace with chat class
  bool split, merge, first_click, second_click;
  PixelCoordinate penultimate_click;
  PixelCoordinate last_click;
  SDL_Event event;

  void handleKeyDown();

  void handleKeyUp();

  void handleMouseButtonLeft(SDL_MouseButtonEvent &mouse);

  void handleMouseButtonRight(SDL_MouseButtonEvent &mouse);

  void handleWindowChange(SDL_WindowEvent &window_event);

  void handleTextInput(const std::string &text);

public:
  explicit EventHandlerThread(Window &window, Game &game);

  // Event loop
  void run() override;

  bool isOpen();
};


#endif //QUANTUM_CHESS_PROJ_EVENT_HANDLER_THREAD_H
