#ifndef QUANTUM_CHESS_PROJ_EVENT_HANDLER_THREAD_H
#define QUANTUM_CHESS_PROJ_EVENT_HANDLER_THREAD_H

#include "../game/game.h"
#include "handler_thread.h"
#include "drawables/drawable_board.h"
#include "../../common/thread.h"
#include "../logic/text_entry.h"
#include <SDL2/SDL.h>
#include <string>

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

  // Toggle music, sounds or special move options according to the pressed key
  void handleKeyDown();

  // Toggle special move options according to the key
  void handleKeyUp();

  // Handle chessman movement, splitting and merging if click is on the board
  // Otherwise handle chat input
  void handleMouseButtonLeft(SDL_MouseButtonEvent &mouse);

  // Handle entangled and quantum chessmen relations
  void handleMouseButtonRight(SDL_MouseButtonEvent &mouse);

  // Resize the game window
  void handleWindowChange(const SDL_WindowEvent &window_event);

  // Read text input if enabled
  void handleTextInput(const std::string &text);

  // Setup movement, split and merge first click
  void handleUserFirstClick(const PixelCoordinate &pixel);

  // Setup movement, split and merge second click
  void handleUserSecondClick(const PixelCoordinate &pixel);

  // Setup split and merge third click
  void handleUserThirdClick(const PixelCoordinate &pixel);

public:
  explicit EventHandlerThread(Window &window, Game &game,
                              Chat &chat_, TextEntry &text_entry);

  // Event loop
  void run() override;
};


#endif //QUANTUM_CHESS_PROJ_EVENT_HANDLER_THREAD_H
