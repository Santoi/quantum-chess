#ifndef QUANTUM_CHESS_PROJ_LOGIN_STATE_HANDLER_H
#define QUANTUM_CHESS_PROJ_LOGIN_STATE_HANDLER_H

#include "login.h"
#include "login_state.h"
#include "../sdl/renderer.h"
#include <memory>
#include <mutex>

class LoginScene;

class LoginState;

class Button;

class TextEntryButton;

class LoginStateHandler {
protected:
  Login &login;
  ButtonSpriteRepository &button_repository;
  TextSpriteRepository &text_repository;
  std::unique_ptr<LoginState> current_state;
  std::mutex mutex;

public:
  LoginStateHandler() = delete;

  explicit LoginStateHandler(Login &login,
                             ButtonSpriteRepository &button_repository,
                             TextSpriteRepository &text_repository);

  //Returns call to current_state clientIsConnectedToMatch method.
  bool clientIsConnectedToMatch();

  //Calls current state's same name method.
  void fillWithActiveButtons(
          std::list<std::reference_wrapper<Button>> &active_buttons);

  //Calls current state's same name method.
  void fillWithActiveTextEntryButtons(
          std::list<std::reference_wrapper<TextEntryButton>> &active_text_entries);

  //It calls current state's processTokens method and handles its return int (or exception
  //throwing) accordingly.
  void processTokens(std::list<std::string> &&tokens);

  //Calls current state's same method with same parameter.
  void render(LoginScene &login_scene);
  
  ~LoginStateHandler() = default;

  //Calls current state's same name method.
  void resetAllButtonsToNotPressedState();
};

#endif //QUANTUM_CHESS_PROJ_LOGIN_STATE_HANDLER_H
