#ifndef QUANTUM_CHESS_PROJ_LOGIN_SCENE_H
#define QUANTUM_CHESS_PROJ_LOGIN_SCENE_H

#include "window.h"
#include "../login/login_state.h"
#include "button.h"
#include "chat/drawable_container.h"
#include "text_entry_button.h"
#include "scene.h"
#include "../login/login_state_handler.h"

class LoginStateHandler;

class TextureSprite;

class LoginScene : public Scene {
private:
  LoginStateHandler &login_state_handler;

  void setConnectionButtonsDimensions(Button &connect_button,
                                      TextEntryButton &ip_text_entry,
                                      TextEntryButton &port_text_entry);

public:

  LoginScene() = delete;

  LoginScene(LoginStateHandler &login_state_handler, Window &window);

  void render();

  void renderMatchButtons(std::list<std::unique_ptr<Button>> &match_buttons);

  void renderConnectedSprite(TextureSprite &texture);

  void renderIPAndPortFields(Button &connect_button,
                             TextEntryButton &ip_text_entry,
                             TextEntryButton &port_text_entry);

  void renderRolesButtons(Button &white_role_button, Button &black_role_button,
                          Button &spectator_role_button);
};


#endif //QUANTUM_CHESS_PROJ_LOGIN_SCENE_H
