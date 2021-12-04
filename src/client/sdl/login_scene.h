#ifndef QUANTUM_CHESS_PROJ_LOGIN_SCENE_H
#define QUANTUM_CHESS_PROJ_LOGIN_SCENE_H

#include "window.h"
#include "../login/login_state_handler.h"
#include "button.h"
#include "text_entry_button.h"
#include "scene.h"

class LoginStateHandler;

class TextureSprite;

class LoginScene : public Scene {
private:
//  int scale;
  LoginStateHandler &login_state_handler;
  DrawableTextEntryButton ip;
  DrawableTextEntryButton port;
  DrawableTextEntryButton nickname;
  DrawableButton submit;
  DrawableContainer <DrawableButton> matches;
  DrawableButton new_match;
  DrawableButton refresh;

public:

  LoginScene() = delete;

  LoginScene(LoginStateHandler &login_state_handler_, Window &window);

//  void setScale(const int& scale_);

  void render();

  void renderMatchButtons(std::vector<std::unique_ptr<Button>> &match_buttons);

  void renderConnectedSprite(TextureSprite &texture);

  void renderIPAndPortFields(Button &connect_button,
                             TextEntryButton &ip_text_entry,
                             TextEntryButton &port_text_entry);
};


#endif //QUANTUM_CHESS_PROJ_LOGIN_SCENE_H
