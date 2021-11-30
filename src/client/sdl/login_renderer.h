#ifndef QUANTUM_CHESS_PROJ_LOGIN_RENDERER_H
#define QUANTUM_CHESS_PROJ_LOGIN_RENDERER_H

#include "window.h"
#include "login_state_handler.h"
#include "button.h"
#include "text_entry_button.h"

class LoginStateHandler;

class LoginRenderer {
private:
  int scale;
  LoginStateHandler &login_state_handler;

public:

  LoginRenderer() = delete;

  LoginRenderer(LoginStateHandler &login_state_handler_, Window &window);

  void setScale(const int& scale_);

  void render();

  void renderIPAndPortFields(ConnectButton &connect_button,
                             TextEntryButton &ip_text_entry,
                             TextEntryButton &port_text_entry);
};


#endif //QUANTUM_CHESS_PROJ_LOGIN_RENDERER_H
