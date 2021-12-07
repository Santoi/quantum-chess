#ifndef QUANTUM_CHESS_PROJ_LOGIN_HANDLER_THREAD_H
#define QUANTUM_CHESS_PROJ_LOGIN_HANDLER_THREAD_H

#include "../sdl/handler_thread.h"
#include "login.h"
#include "login_state.h"
#include "login_state_handler.h"
#include "../sdl/pixel_coordinate.h"
#include <SDL2/SDL.h>
#include <atomic>

class LoginHandlerThread : public HandlerThread {
private:
  Login &login;
  LoginStateHandler &login_state_handler;
  PixelCoordinate last_click;
  SDL_Event event{};
  bool expecting_text_entry;
  bool was_closed_;

public:
  LoginHandlerThread() = delete;

  LoginHandlerThread(Login &login, LoginStateHandler &login_state_handler);

  // Event loop
  void run() override;

  ~LoginHandlerThread() override = default;

  bool was_closed() const;

private:

  void handleTextInput(const std::string &input);

  void handleMouseButtonLeft(SDL_MouseButtonEvent &mouse);

  void handleKeyDown();
};

#endif //QUANTUM_CHESS_PROJ_LOGIN_HANDLER_THREAD_H
