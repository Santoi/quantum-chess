#ifndef QUANTUM_CHESS_PROJ_LOGIN_HANDLER_THREAD_H
#define QUANTUM_CHESS_PROJ_LOGIN_HANDLER_THREAD_H

#include "../sdl/handler_thread.h"
#include "login.h"
#include "login_state.h"
#include "login_state_handler.h"
#include "../sdl/pixel_coordinate.h"
#include <SDL2/SDL.h>
#include <atomic>
#include <string>

class LoginHandlerThread : public HandlerThread {
private:
  Login &login;
  LoginStateHandler &login_state_handler;
  SDL_Event event;
  bool expecting_text_entry;
  bool was_closed_;

public:
  LoginHandlerThread() = delete;

  //Creates LoginHandlerThread setting was_closed_ = false,
  //expecting_text_entry = false and parent's attribute open = true.
  LoginHandlerThread(Login &login, LoginStateHandler &login_state_handler);

  //Does event loop while client is not connected to match. After finishing loop
  //open is set to false. If loop was not finished because client closed window,
  //open is set to false and was_closed is set to true.
  void run() override;

  ~LoginHandlerThread() override = default;

  //Returns was_closed boolean.
  bool was_closed() const;

private:
  void handleTextInput(const std::string &input);

  void handleMouseButtonLeft(const SDL_MouseButtonEvent &mouse);

  void handleKeyDown();

  void handleMouseButtonLeft();
};

#endif //QUANTUM_CHESS_PROJ_LOGIN_HANDLER_THREAD_H
